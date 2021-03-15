# Git Tips

## How to use `gitsubmodule`


Show status
-----------

```bash
git submodule status --recursive
```

Update all submodule
--------------------

#### Add project

```bash
# Clone to the current folder: 
git submodule add -b <branch-name> <repository> <local-folder-name-to-be-breated>
git submodule init

```


## Update gitsubmodule from remote
git submodule update --recursive --remote

#### Fetch
```bash
git submodule update --recursive
```

#### Pull
```bash
git pull --recurse-submodules
```


## Tag


### Tag a version

```bash
git tag -a [tag-name] -m "commit"
```

### Push a tag

```bash
git push origin [tag-name]
```

### List all tags

```bash
git tag
```

## Plotting with diagrams

[Diagram](https://app.diagrams.net/) features uploading to Github repository, making the drawing up-to-date easily!


