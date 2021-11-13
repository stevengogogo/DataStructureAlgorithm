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

```git
git submodule foreach git pull origin main
```

Warning: please make sure to push all the branch, then update the main repo

```git
git submodule update --recursive --remote
```

```git
git pull --recurse-submodules
```

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


## Reference

Tutorial of updateing submodules: https://stackoverflow.com/questions/1030169/easy-way-to-pull-latest-of-all-git-submodules