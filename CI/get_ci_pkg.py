#!/usr/bin/env python3
# -*- encoding:utf-8 -*-

import sys
import json
from os import environ as env
from urllib.request import Request, urlopen
from operator import itemgetter

retFlag=True
for var in ["MAJA_ARTIFACTS", "CI_PROJECT_ID", "CI_COMMIT_SHA"]:
  if not var in env:
    retFlag=False
    print("ERROR: missing \"{}\" environment variable".format(var))
if not retFlag:
  sys.exit(1)

def get_gitlab_objects(req):
  with urlopen(req) as f:
    nb_pages=int(f.headers["X-Total-Pages"])
    raw = f.read()
    encoding = f.info().get_content_charset('utf-8')
    content = json.loads(raw.decode(encoding))
  if nb_pages > 1:
    print("Check all {} pages...".format(nb_pages))
    orig_url = req.full_url
    for page in range(2,nb_pages):
      req.full_url = orig_url+"&page={}".format(page)
      with urlopen(req) as f:
        raw = f.read()
        encoding = f.info().get_content_charset('utf-8')
        content += json.loads(raw.decode(encoding))
  return content

url_base="https://gitlab.orfeo-toolbox.org/api/v4/projects/{}/".format(env["CI_PROJECT_ID"])

pipelineRequest = Request(
  url_base+"pipelines?status=success&sha={}".format(env["CI_COMMIT_SHA"]),
  headers={"PRIVATE-TOKEN":env["MAJA_ARTIFACTS"]})

pipelines = get_gitlab_objects(pipelineRequest)

print("Found {} pipelines".format(len(pipelines)))

targetName="build-centos7"

for ppl in pipelines:
  pplJobs = Request(
    url_base+"pipelines/{}/jobs?scope=success".format(ppl['id']),
    headers={"PRIVATE-TOKEN":env["MAJA_ARTIFACTS"]})
  jobs = get_gitlab_objects(pplJobs)
  targetJobs = [job for job in jobs if (job["name"]==targetName)]
  if targetJobs:
    sortedJobs = sorted(targetJobs, key=itemgetter('id'), reverse=True)
    targetId = sortedJobs[0]['id']
    print("Target job: "+str(targetId))
    if 'artifacts_file' in sortedJobs[0]:
      print("Downloading artifacts from target job")
      artReq = Request(
        url_base+"jobs/{}/artifacts".format(targetId),
        headers={"PRIVATE-TOKEN":env["MAJA_ARTIFACTS"]})
      with urlopen(artReq) as f:
        with open("artifacts.zip","wb") as out:
          out.write(f.read())
    else:
      print("Missing artifacts in target job!")
    break
