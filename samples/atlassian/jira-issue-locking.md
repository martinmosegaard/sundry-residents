# Jira Issue Locking

How editing conflicts are handled in Jira and how issue locking can help.

## Problem: Editing conflicts

If two users edit and try to update the same issue at the same time, the last edit wins.
Imagine an issue with these properties:

* __Title__: The dog is on fire
* __Description__: TODO
* __Priority__: Major
* __Assignee__: Unassigned

Then imagine users `Alice` and `Bob` edit the issue at the same time. `Alice` submits
her changes just a moment before `Bob`. Their changes look like this:

`Alice`:

* __Title__: The dog may sometimes catch fire
* __Description__: Occasionally, we see this problem
* __Priority__: Minor

`Bob`:

* __Description__: This is really bad! I'm pretty sure Alice knows how to fix it.
* __Assignee__: Alice

Both updates get submitted, one after the other. The result is that Bob's changes
overwrites Alice's. This __includes__ fields that Bob did not change, so the result looks
like this:

* __Title__: The dog is on fire
* __Description__: This is really bad! I'm pretty sure Alice knows how to fix it.
* __Priority__: Major
* __Assignee__: Alice

None of the users see any kind of warning. The history is visible in the `All` tab, but
you have to look for it.

## Issue Locking plugin

A workaround is to use a plugin called `Issue Lock for JIRA`, as described here:
<https://jira.atlassian.com/browse/JRA-6146>

This is a commercial plugin and must be enabled per project. It takes an issue edit lock
per user and shows red/green status bars at the bottom of the window when conflicts occur.

## A manual solution

A manual solution using custom fields is described here: <https://lukehalliwell.wordpress.com/2009/09/01/my-love-for-plugins-reaffirmed/>
although it does not provide all the details.
