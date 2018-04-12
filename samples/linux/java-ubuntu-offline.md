# Install Java on Ubuntu offline

Let's say we have a Ubuntu machine without Internet access, no configuration
management tools, and want to install Java JRE. Do something like this.

Copy the installer to the machine and unpack it:

```
scp jre-8u121-linux-x64.tar.gz user@remote-machine:/tmp/
ssh user@remote-machine
sudo mkdir /usr/local/java
sudo tar xzvf /tmp/jre-8u121-linux-x64.tar.gz -C /usr/local/java/
```

Update environment:

```
sudo vim /etc/profile
```

and add:

```
JAVA_HOME=/usr/local/java/jre1.8.0_121
PATH=$PATH:$JAVA_HOME/bin
export JAVA_HOME
export PATH
```

Update alternatives:

```
sudo update-alternatives --install "/usr/bin/java" "java" "/usr/local/java/jre1.8.0_121/bin/java" 1
sudo update-alternatives --set java /usr/local/java/jre1.8.0_121/bin/java
```

