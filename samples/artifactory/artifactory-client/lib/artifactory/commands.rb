require 'thor'
require 'artifactory/commands/cli_base'
require 'artifactory/commands/repository'

module Artifactory
  # Collection of commands
  module Commands
  end

  # Declaration of commands
  class Command < Thor
    desc 'repository SUBCOMMAND ...ARGS', 'manage repositories'
    subcommand 'repository', Commands::Repository
  end
end
