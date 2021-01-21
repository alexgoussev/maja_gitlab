# How to contribute ?

Thank you for taking the time to contribute to MAJA! This document will guide you
through the workflow and best practices you need to know to send your
contribution.

There are many ways to contribute:

* [Reporting a bug](#reporting-bugs)
* [Making a feature request](#feature-requests-and-discussions)
* [Contributing code (C++, Python, CMake, etc.)](#code-contribution)
* [Improving documentation](#documentation-improvements)
* [GitLab guidelines](#gitlab-guidelines)


Our main workflow uses GitLab for source control, issues and task tracking. We
use a self-hosted GitLab instance:

https://gitlab.orfeo-toolbox.org/maja/maja



## Reporting bugs

If you have found a bug, you can first search [search the existing issues](https://gitlab.orfeo-toolbox.org/maja/maja/-/issues?scope=all&utf8=%E2%9C%93&state=opened&label_name[]=FA)
to see if it has already been reported.

If it's a new bug, please [open a new issue](https://gitlab.orfeo-toolbox.org/maja/maja/-/issues/new?issue%5Bassignee_id%5D=&issue%5Bmilestone_id%5D=#) on GitLab using the FA issue template that will help you to provide all important information and
help fixing the bug quicker. Remember to add as much information as possible!

## Feature requests and discussions

Feature requests are welcome! You are welcome to simply [open an issue]((https://gitlab.orfeo-toolbox.org/maja/maja/-/issues/new?issue%5Bassignee_id%5D=&issue%5Bmilestone_id%5D=#)) on GitLab using the DM template
and discuss your idea there.

## Code contribution

Clone the repository, create a feature branch, commit your changes, push the
feature branch to the main repository and then send a merge request.


### Commit message

On your feature branch, write a good [commit message](https:branch//xkcd.com/1296/):
short and descriptive. If fixing an issue or bug, put the issue number in the
commit message so that GitLab can [cross-link it](https://docs.gitlab.com/ce/user/project/issues/crosslinking_issues.html).
You can prefix your commit message with an indicating flag (DOC, BUG, PKG,
TEST, SuperBuild, etc.).

Standard prefixes for commit messages:

    BUG: Fix for runtime crash or incorrect result
    COMP: Compiler error or warning fix
    DOC: Documentation change
    ENH: New functionality
    PERF: Performance improvement
    STYLE: No logic impact (indentation, comments)
    WIP: Work In Progress not ready for merge

For example, here are some good commit messages:

    BUG: #1701 Warn users if parameter string is unset
    DOC: Fix typo in Monteverdi French translation
    COMP: Allow GeoTIFF and TIFF to be disabled when no 3rd party drags them

### Merge request

Your contribution is ready to be added to the main repository? Send a Merge
Request against the `develop` branch on GitLab using the merge request
template. The merge request will then be discussed by the community and the core team.

* Merge requests can not be merged until all discussions have been resolved (this is enforced by GitLab)
* The merger is responsible for checking that the branch is up-to-date with develop
* Merge requests can be merged only from core maintainers (members of Main Repositories group in Gitlab with at least "Maintainer" level) with push access to develop
* Merge requests can be merged once the CI pipeline passes successfully. See
  next section for details on the CI pipelines.

### Contribution license agreement

This project requires that contributors sign out a [Contributor License
Agreement](https://en.wikipedia.org/wiki/Contributor_License_Agreement). The
purpose of this CLA is to ensure that the project has the necessary ownership or
grants of rights over all contributions to allow them to distribute under the
chosen license (Apache License Version 2.0)

The copyright owner (or owner's agent) must be mentioned in headers of all
modified source files and also added to the NOTICE
file.


## Documentation improvements

The main MAJA documentation are the UserManual and the ConceptionManual. The source is hosted in the main MAJA repository in the Documentation/ directory. Then, to
contribute documentation use the same workflow as for code contributions (see below).
See also the Documentation/readme.txt file for help on building the documentation.


## GitLab guidelines

### Labels and Milestones

In order to organize the issues in our GitLab instance, we use both labels and
milestones.

The milestones should be used to track in which release a feature is merged.
GitLab can then provide a summary of all features and bugs added to a given release
version.

Regarding labels, we use the following set:
* ~FA: Bug, crash or unexpected behavior, reported by a user or a developer
* ~DM: Feature request expressed by a user/developer
* ~CS Analysis: Issue being analysed by CS (core developers and maintainers)
* ~Confirmed: CS confirmed anomaly
* ~ToDo: action is planned
* ~Doing: Work in progress
* ~Waiting for answer: CS is waiting for answer
* ~Waiting for context: CS is waiting for a detailed context
* ~Not reproductible: FA not reproductible
* ~Suspended: Suspended issue
* ~To be verified CNES: Verification to be done by CNES
* ~Not accepted: Issue correction not accepted by CNES
* ~Accepted: Issue correction accepted by CNES. To be closed by QA.




### Versioning

We use [semantic versioning](https://semver.org/). See the website for the full spec, in summary:

> Given a version number MAJOR.MINOR.PATCH, increment the:
>
>  1. MAJOR version when you make incompatible API changes,
>  2. MINOR version when you add functionality in a backwards-compatible manner, and
>  3. PATCH version when you make backwards-compatible bug fixes.
>
> Additional labels for pre-release and build metadata are available as extensions to the MAJOR.MINOR.PATCH format.

The develop branch is always the place where the upcoming major or minor release is worked on. Patch releases are done on release branches, for example 4.3.0 could be found on the release_v4.3.0 branch.

For the purpose of defining backwards compatibility, the API covers (not an exhaustive list): the C++ API, the Python bindings, application names, application parameters, output format and interpretation of input data.

When we deprecate part of our public API, we should do two things: (1) update our documentation to let users know about the change, (2) issue a new minor or major release with the deprecation in place.