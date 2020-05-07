---
name: General Issue (FA)
about: Use this template for reporting an anomaly.

---

<em>Please make sure that this is a bug. As per our [GitHub Policy](https://gitlab.cnes.fr/maja/maja/blob/develop/ISSUE.md), we only address code/doc bugs, performance issues and build/installation issues on GitHub.</em>

**System information**

- OS Platform and Distribution (e.g., Linux Ubuntu 16.04):
- Maja installed from (source or binary):
- Maja version (use command below):
- Maja commit sha (if Maja is installed from source):
- Python version (From binpkg or custom):
- Complementary info (i.e. GCC/Compiler version)

You can collect some of this information using our environment capture
[script](https://gitlab.cnes.fr/maja/maja/blob/develop/maja_env_collect.sh)

You can also obtain the Maja version with:
```
maja --version
```

**Describe the current behavior**


**Describe the expected behavior**


**Urgency/Criticity**

- Urgency (Select Low/Medium/High):
- Criticity (Select Low/Medium/High):

**Code to reproduce the issue**

Provide a reproducible test case that is the bare minimum necessary to generate the problem.
Include any logs or source code that would be helpful to diagnose the problem. If including tracebacks, please include the full traceback. Large logs and files should be attached.

A path to a context folder is also accepted. Please note the [Context policy](https://gitlab.cnes.fr/maja/maja/blob/develop/ISSUE.md#Contexts)

**Correction**

(Optional) Provide a version number (Major.Minor.Patch, e.g. 3.2.1) when the correction shall be introduced.
