Note1: that this version differs (from the Docker one) bcs of the absence of the "err" directory (mistaken questions files are directly saved onto the main dir)
UPDATE1: Added the possibility to save the current state of question answered, in order to then proceed in a second moment with the non-answered ones.

---------------------------------------------------------------------------------------------------------

I've built a (really simple and raw) cpp application to let the user train onto questions.
The app provides you randomly chosen questions from a pool that I'll personally update throughout the courses, together with three possible closed answers. You have to choose your preferred answer (only one is right) and the app will let you know whether you were right or not (in that second case, specifying which one was the correct answer). A the very end (either when you finish the questions or when you decide to stop typing "0") you'll be provided with a percentage of correct answers.
Also, you can optionally specify (at the end) a file where the app will append all the mistaken questions (the intended behaviour is to repeat questions when you do them wrong again, so when providing the same fname the app will append and not overwrite).
I'm sharing this with all of you also to let you add new questions and improve the pool!
Finally, please tell me if you notice bugs when you use the app :D

Some technical and installation info following:

1) The first and intended method to use the app is with Docker.
When I'll update the questions (with mine or yours) I'll run an automatic script that pushes everything onto a Docker Hub public repository. This means that (after having installed Docker) you'll always have the chance to run the very newest version of the app by copying this following one-liner:

docker run --pull always -v err:/app/err/ -it lorenzofoschi/questions ./app fstt.txt

In order to access the files with the mistaken questions that you created in runtime, you can type:

docker run --pull always -v err:/app/err/ -it lorenzofoschi/questions ./app ./err/<fileWhereUSavedMistakenQuestions>
f.e, if you provided the fname "imdumb.txt" at the end:
docker run --pull always -v err:/app/err/ -it lorenzofoschi/questions ./app ./err/imdumb.txt

2) If you prefer I also put the code and the txt files into this GitHub repo.
I encourage you to use the Discussion page into this GitHub Repository to provide your suggested formatted questions to let me add them to the app, in order to build it as a community!

The format of the questions to be read by the app is the following, so provide them in this format if you'll decide to do so:
<question> * <answer1> * <answer2> * <answer3> * <number of the right answer>
f.e :
What color is the sky? * red * blue * green * 2

Thank you for your attention, hoping that this stuff will turn out to be somehow useful
Lorenzo

