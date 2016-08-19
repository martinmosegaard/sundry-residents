require 'rbvmomi'

# Connect to a vCenter Server or a standalone ESX host.
class Connect
  # Connect to an ESX or vCenter host and return the service instance
  # used to browse the inventory of managed objects.
  def self.login(host, user, password)
    vim = RbVmomi::VIM.connect host: host, user: user, password: password, insecure: true
    vim.serviceInstance
  end
end
