Gradescope PAs, espically as we start using GPUs in the grading environment and have limited compute resources for grading will
be on a cooldown of an hour. (As always, start early and start often!)

Due to how Gradescope API's work, the cooldown is not a simple rate limit of one per hour. 
If you submit during the cooldown, you will not recieve a grade and be given the error 

"You are only allowed one submission per hour. Using results from run occuring at <INSERT DATETIME OBJECT HERE>"

This restarts the cooldown, meaning you must wait another **ADDITIONAL** hour until the cooldown completes.

Below is the pseduocode for how this rate limiter works 

.. code-block:: python
    User submits a new submission
    Get submissions object from gradescope
    Get time from submissions.prev_submitions
    Get current time
    If current time - submissions.prev_submitions < hour
        Return rate limit
    else
        Grade

Note that by submiting, you change the current submission. 

Here is a scenrio to illustrate this:
- At 8:00pm you submit for the frist time. You will be graded.
- At 8:30pm you submit again, gradescope checks the previous submission, sees the submission time was 8:00pm which is less than an hour. You are blocked from getting regraded.
- At 9:00pm you submit again, gradescope checks the previous submission, sees the submission time was **8:30pm** which is less than an hour. You are blocked from getting regraded.

At this point, you may only submit after 10pm to have a submission be graded, despite your last "successful" submission being at 8pm. 

TLDR: If you submit to gradescope, wait an hour before your next submission. If you submit again before that hour passes, restart your stopwatch for another hour. Do your testing locally or on DSMLP