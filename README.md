# Game-of-Life
This is a mostly complete version of Conway's game of life that has been written in basic C++. It follows all of the standard rules that can be found in the wikipedia page for the game, and has a generations counter and an alive counter. The rules can be found in [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

It is not the most efficient implementation as it checks every pixel's neighbourhood instead of some of the smart approaches, however as this project was done without the benefits of google or LLMs I could not figure out the smart approaches. Initial attempts to add a detection of whether or not a state was stuck in a loop was hampered by the fact that it is a Godel unsolvable problem whether or not a situation will change. There are ways to detect <10 cycle states, but this is not reliable and awful for memory.

This was a very fun project, and is the first piece of software I feel comfortable saying I have "finished", even if it is remarkably simple.

As this is a very simple project and a very common codebase this will not be licensed and contributions will not be accepted.

### How to run
`g++ main.cpp -o main`
