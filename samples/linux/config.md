# Configuration

## Hostname

```
sudo vim /etc/hostname
sudo vim /etc/hosts
```

## Static IP

```
sudo vim /etc/network/interfaces

auto eth0
iface eth0 inet static
address 10.0.0.100
netmask 255.255.255.0
gateway 10.0.0.1
```

## Password of current user

```
passwd
```
