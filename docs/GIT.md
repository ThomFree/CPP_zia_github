# Workflow git
This document detail how we use git in this project.

## Commit style

In order to keep things organized, here is the commit style we must respect.

Doing so will not only clarify the changes we made with each commit, but also increase our capacity to  summarize those changes.

- Every commit must be in English.

- Each commit should start with a square bracket enclosed key to declare the reason of the commit. Those  keys can be found among those:

	[ADD] -- if you add files, features, and so on

	[WIP] -- if you're still working on the feature, fix or whatever you're working on AND your work  is still unfit to 	immediate use

	[FIX] -- if you were working on a bug or any form of default that you corrected

	[DEL] -- if you removed files, features, assets, and so on

	[CHG] -- if you change something without adding any features or stuff

- Each commit should then be followed by a single line (50 characters MAX) explaining basics of the changes.
	For instance, you can have messages such as "[ADD] Collision system".

- Finally, and if needed only, you can add a body to your commits, separated from the "[KEY] Header" line by a blank line, and this body should be used ONLY to detail your commit (in case there's a fix giving everyone a  headache and you might want to explain why or what you did to fix it).

Let's keep the work flow as clean as possible in order to navigate more easily.

## Workflow

You must create a branch for each feature. These branches will then be pushed to the central repository for backup / collaboration. However, instead of creating a new branch from master, the feature branches use the develop branch as a parent branch. When a feature is complete, it is again merged into develop. The features never communicate directly with the master branch.

Git Workflow - Branches of functionality

![alt text](https://cdn-images-1.medium.com/max/1600/1*g8oYoPTCdPUjMTeN020WNw.png "Git Workflow - Master Dev Feature")

For all intents and purposes, note that when feature branches are associated with the develop branch, they are the “feature branch workflow”. However, the Gitflow workflow is not limited to this.  
  
Feature branches are usually created from the last develop branch.
