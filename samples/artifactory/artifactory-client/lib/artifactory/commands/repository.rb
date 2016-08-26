require 'json'

module Artifactory
  module Commands
    # Commands for managing a repository.
    class Repository < CliBase
      desc 'create-from-file', 'Create repositories from a file'
      method_option :file, type: :string, required: true, desc: 'JSON file with repository info'
      def create_from_file
        configure_target_endpoint

        file = File.read(options[:file])
        repos_hash = JSON.parse(file)
        repos_hash = filter(repos_hash)
        repos_hash.each { |h| save(h) }
      end

      desc 'write', 'Write a JSON file with all local repositories'
      method_option :file, type: :string, required: true, desc: 'Name of target JSON file'
      def write
        configure_source_endpoint

        repos = Artifactory::Resource::Repository.all
        repos = filter(repos)
        repos = repos.map { |r| r.rclass == 'remote' ? add_url_for_remote(r) : r }

        json = to_json(repos)
        File.open(options[:file], 'w') do |f|
          f.write(json)
        end
        puts "[#{endpoint}] Repositories written to #{options[:file]}"
      end

      private

      # Select repositories to include.
      def filter(repos)
        ignore_list = repositories_to_ignore
        repos.select do |r|
          if r.is_a? Artifactory::Resource::Repository
            should_include?(r.rclass, r.key, ignore_list)
          elsif r.is_a? Hash
            should_include?(r['rclass'], r['key'], ignore_list)
          end
        end
      end

      # Test if a repository should be included.
      # @param rclass Repository class
      # @param key Repository key
      # @param ignore_list List of repository keys to ignore
      def should_include?(rclass, key, ignore_list)
        not_virtual = %w(local remote).include? rclass
        not_ignored = !(ignore_list.include? key)
        not_virtual && not_ignored
      end

      # The artifactory-client does not have a URL attribute for repositories,
      # but we need that when creating a remote repository.
      def add_url_for_remote(repo)
        raw_info = Artifactory.get("/api/repositories/#{repo.key}")
        Artifactory::ClientExtension::RemoteRepository.new(
          key: repo.key,
          package_type: repo.package_type,
          description: repo.description,
          url: raw_info['url'],
          rclass: repo.rclass
        )
      end

      # Create (or update a repository).
      # A remote repository needs to be created using a raw PUT request,
      # because the artifactory-client Repository class does not have a
      # URL attribute.
      def save(hash)
        puts "[#{endpoint}] Saving repository: #{hash['key']}, class=#{hash['rclass']}"
        if hash['rclass'] == 'local'
          save_local hash
        elsif hash['rclass'] == 'remote'
          save_remote hash
        end
      end

      def save_local(hash)
        repo = Artifactory::Resource::Repository.new(
          key: hash['key'],
          description: hash['description'],
          package_type: hash['packageType'],
          repo_layout_ref: hash['layout']
        )
        repo.save
      end

      def save_remote(hash)
        json = JSON.generate hash
        headers = { 'Content-Type' =>
          'application/vnd.org.jfrog.artifactory.repositories.RemoteRepositoryConfiguration+json' }
        Artifactory.put("/api/repositories/#{hash['key']}", json, headers)
      end

      def to_json(repos)
        hash = repos.map do |r|
          if r.is_a? Artifactory::ClientExtension::RemoteRepository
            { rclass: r.rclass,
              key: r.key,
              description: r.description,
              packageType: r.package_type,
              layout: r.repo_layout_ref,
              url: r.url }
          else
            { rclass: r.rclass,
              key: r.key,
              description: r.description,
              packageType: r.package_type,
              layout: r.repo_layout_ref }
          end
        end
        JSON.pretty_generate hash
      end
    end
  end
end
