job('pretested-integration-test') {

  description('Using Pretested Integration plugin with Job DSL 1.44+')

  scm {
    git('https://github.com/Praqma/DAME.git')
  }
  configure { project ->
    // First remove 'create a tag for every build'
    project / scm / extensions {
    }
    // Then add custom extensions
    project / scm / extensions << 'hudson.plugins.git.extensions.impl.CleanCheckout'()
    project / scm / extensions << 'hudson.plugins.git.extensions.impl.PruneStaleBranch'()
  }

  steps {
    shell('cat Readme.md')
  }

  wrappers {
    pretestedIntegration("SQUASHED","master","origin")
  }

  publishers {
    pretestedIntegration()
  }
}
