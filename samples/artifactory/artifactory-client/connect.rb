require 'artifactory'

include Artifactory::Resource

Artifactory.configure do |config|
  config.endpoint = 'http://localhost:8081/artifactory'
  config.username = 'admin'
  config.password = 'password'
  config.ssl_verify = false
end

system = System.version
puts "Version: #{system['version']}"
puts "License: #{system['license']}"

repos = Repository.all
puts "Number of repositories: #{repos.length}"
repos.each { |r| puts "#{r.key} - #{r.description}" }
