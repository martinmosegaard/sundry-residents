require 'artifactory'

include Artifactory::Resource

Artifactory.configure do |config|
  config.endpoint = 'http://localhost:8081/artifactory'
  config.username = 'admin'
  config.password = 'password'
  config.ssl_verify = false
end

puts System.info
puts System.version

repos = Repository.all
puts "Number of repositories: #{repos.length}"
