# Connect to VMware vSphere (vCenter Server or standalone ESX host).
# Get an interactive session with a datacenter object called dc:
#
#   pry -Ilib vsphere.rb
#   [1] pry(main)> dc.name
#   => "ha-datacenter"

require 'connect'
require 'pry'

host     = ENV['vsphere_host'] || '192.168.99.100'
user     = ENV['vsphere_user'] || 'root'
password = ENV['vsphere_password'] || raise('vsphere_password not set')

service_instance = Connect.login(host, user, password)
dc = service_instance.find_datacenter('ha-datacenter') || raise('datacenter not found')

puts "Datacenter [dc]: #{dc.name}"

Pry.start
