# Windows

Tips and tricks.

## Hostname and IP configuration

### Get

```sh
hostname
ipconfig
ipconfig /all
```

### Set

Run as administrator.

Static IP:

```sh
netsh interface ip set address name=<adapter> static <ip> <mask> <gateway>
netsh interface ip set address name="Adapter name" static 172.20.123.1 255.255.255.0 172.20.123.254
```

Dynamic IP:

```sh
netsh interface ip set address name="Adapter name" dynamic
```

Hostname in powershell:

```sh
netdom renamecomputer "$env:COMPUTERNAME" /newname thename
```

Hostname in command prompt:

```sh
netdom renamecomputer %COMPUTERNAME% /newname thename
```

Hostname in command prompt, if using `netdom` does not work (for example Windows XP not in a domain):

```sh
wmic computersystem where name='%computername%' call rename name='thename'
```

When using `wmic`, you have to reboot afterwards. It will not prompt you.

## Cannot rename this connection. A connection with the name you specified already exists. Specify a different name

```sh
set devmgr_show_nonpresent_devices=1
devmgmt.msc
```

- Show hidden devices
- Uninstall dimmed adapters

## Get OS architecture

```sh
wmic os get osarchitecture
```
