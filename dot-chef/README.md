# Dot-chef folder

Used to set up a laptop using Chef in local mode.

## Prerequisites

- ChefDK

## Usage

Go to the `.chef` folder where the `Berksfile` is and download all required cookbooks:

```sh
cd ~/.chef
berks vendor cookbooks/
```

Run Chef Client in local mode with a run list of what to install:

```sh
chef-client --local-mode --runlist 'recipe[atom::default]'
```
