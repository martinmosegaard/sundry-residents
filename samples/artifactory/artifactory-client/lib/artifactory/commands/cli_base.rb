require 'base64'
require 'uri'
require 'yaml'

module Artifactory
  module Commands
    # Base class for commands.
    class CliBase < Thor
      protected

      def configure_source_endpoint
        config = YAML.load_file('config.yml')
        configure_with config['source']
        puts "[#{endpoint}] Set as source"
      end

      def configure_target_endpoint
        config = YAML.load_file('config.yml')
        configure_with config['target']
        puts "[#{endpoint}] Set as target"
      end

      # Get the Artifactory endpoint, for logging purposes
      def endpoint
        uri = URI(Artifactory.endpoint)
        "#{uri.host}:#{uri.port}"
      end

      # Get an array of repositories to ignore
      def repositories_to_ignore
        config = YAML.load_file('config.yml')
        config['ignore']
      end

      private

      def configure_with(yml)
        Artifactory.configure do |config|
          config.endpoint = yml['endpoint']
          config.username = yml['username']
          config.password = get_password yml['password']
        end
      end

      def get_password(password)
        encoding_prefix = 'base64 '
        if password.start_with? encoding_prefix
          Base64.decode64 password[encoding_prefix.length..-1]
        else
          password
        end
      end
    end
  end
end
