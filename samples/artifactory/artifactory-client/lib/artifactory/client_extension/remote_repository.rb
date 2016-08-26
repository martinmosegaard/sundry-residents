module Artifactory
  module ClientExtension
    # The base repository class does not have a URL attribute,
    # which is important for remote repositories.
    class RemoteRepository < Artifactory::Resource::Repository
      attribute :url
    end
  end
end
