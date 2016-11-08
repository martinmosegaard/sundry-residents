# Plugins

User guide chapter 25, Gradle Plugins.
User guide chapter 39, Writing Custom Plugins.

Gradle does little by itself, all useful features, like compiling Java, is added by
plugins.

Plugins promote reuse and encapsulate logic so build scripts can be declarative.

Two types:

* Script plugin - `apply from 'other.gradle'`
* Binary plugin - `apply plugin: 'java'`

Apply using the plugins DSL:

```sh
plugins {
  id 'java'
  id 'com.jfrog.bintray' version '0.4.1'
}
```

Resolved via `plugins.gradle.org`
