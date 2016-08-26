# Interaction with the Artifactory REST API
module Artifactory
end

require 'artifactory' # from artifactory-client gem
require 'artifactory/commands'
require_relative 'client_extension/remote_repository'
