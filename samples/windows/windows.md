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
