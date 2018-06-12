# Artifact search and cleanup

Use the Artifactory query language, AQL, to search for artifacts. An AQL query can be executed via a cURL POST request or via the `jfrog` CLI tool.

See documentation in the links below.

## JFrog CLI Setup

Credentials can be saved in a config file with the `jfrog rt config` command, but you may need to run it as root for it to actually save the file (and then give yourself read access afterwards).

Put both user and API key:

`jfrog rt config myartifactory --url=https://artifactory.company.com/artifactory/ --user=yourname --apikey=yourkey`

should give a file like this:

```
$ cat ~/.jfrog/jfrog-cli.conf
{
  "artifactory": [
    {
      "url": "https://artifactory.company.com/artifactory/",
      "user": "yourname",
      "apiKey": "yourkey",
      "serverId": "myartifactory",
      "isDefault": true
    }
  ],
  "Version": "1"
}
```

## Example usage

### JFrog CLI

Put your AQL query into a json file. The query in `jfrog-cli-aql.json` finds artifacts in the `libs-release` repo (must be virtual), that matches a path for company artifacts and where artifacts have a property called `branch` with the value `master`.

Then pass it to `jfrog`, possibly with `--dry-run` as to not really delete files:

`jfrog rt del --dry-run --spec=jfrog-cli-aql.json`

### Plain HTTP and AQL

The pure AQL file `aql.json` is a bit simpler and search can be done with a POST request:

`curl -X POST https://artifactory.company.com/artifactory/api/search/aql -u $ARTIFACTORY_USER:$ARTIFACTORY_KEY -T aql.json`

## Links

- https://jfrog.com/knowledge-base/what-is-the-best-way-to-search-for-artifacts/
- https://www.jfrog.com/confluence/display/CLI/CLI+for+JFrog+Artifactory
- https://github.com/jfrog/artifactory-scripts/tree/master/cleanup
