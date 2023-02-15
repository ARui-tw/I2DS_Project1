# CSCi 5105 Project 1: PubSub
[GitHub Repo](https://github.com/ARui-tw/I2DS_Project1)

## Team members and contributions
* Group: 6  
* Team members:  
	* Eric Chen (chen8332@umn.edu)  
	* Sai Vanamala (vanam017@umn.edu)  
	* Rohan Shanbhag (shanb020@umn.edu)  

### Member contributions:
We opted to work together as a team throughout the coding/development process by working together through Discord, meeting generally every night for an hour or two over the course of the project. Each team member shared equal responsibility for overseeing the code written, the design decisions/documentation, and the test cases. All three of us were working together on call to complete the `Join()`, `Leave()`, `Ping()`, `Subscribe()`, `Publish()` and final Server → Client functionality.


## Project Build and Compilation Instructions
In order to build and compile the project
* Compile the server and client  
	`make -f Makefile.communicate`
* Run the server:  
	`./communicate_server`
* Run the client:  
	`./communicate_client localhost`


## Design Document
We decided upon the design of our Publish Subscribe System for Project 1 amongst the three of us, and some specific design decisions we made were as follows:
* We have defined our `MAXCLIENTS` to be 7 as we felt this was a suitable number of clients to demonstrate the functionality of our Publish Subscribe system without overwhelming/overcrowding the subscriber pool
* Our client, upon requesting an article/resource from the server, is kept alive until the publisher publishes an article – with contents – which matches the client’s requirements.
	* As part of this our server is prohibited from publishing articles which lack all three of "type", "originator" and "org", and our clients are unable to make such requests – both instances fail, and instead prompt further user input.
	* Clients will receives the article after they finish the current command.
	* Clients are kept alive until they wish to quit (input "q")
* Our server can handle concurrent requests from clients (to publish/subscribe), and our elected method of handling concurrent requests is to let the server allocate resources on a first-come-first-served basis. This does not prioritize a certain request, and instead requests to publish, subscribe and leave etc. are given equal priority.

## Test Cases
* Note: all client will recieve the article after they finish the current command. So to test if the article is received, the client can use the `ping()` function, which is the "6" option in the menu, to check if the article is received.
* Test Case #1: Normal Condition – Three users join the pool, with two requesting to subscribe to specific articles, and one requesting to publish.
	* How to run:
		* Server:
			* Run the server: `./communicate_server`
		* Client 1:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> "Science;;UMN;"
			* \<user waits until receives article>
			* \<user enters> "q"
		* Client 2 (New terminal window):
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> "Science;;;"
			* \<user waits until receives article>
			* \<user enters> "q"
		* Client 3 (New terminal window):
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "5"
			* \<user enters> "Science;;UMN;Science;;UMN;Science is a systematic approach to understanding the natural world, based on empirical evidence."
			* \<user enters> "q"

	* Expected results:
		* Clients 1 and 2 will receive the article published by Client 3
		* Client 3 does not receive anything since they published the article


* Test Case #2: Failure Condition – We want to ensure that our system will not allow any improperly formatted articles to be subscribed to or published by any clients
	* How to run:
		* Compile the server and client `make -f Makefile.communicate`
		* Server:
			* Run the server: `./communicate_server`
		* Client 1:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> ";;;The FitnessGram PACER test"
		* Client 2:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "5"
			* \<user enters> ";;;The FitnessGram PACER test"

		* Expected results:
			* Client 1 will not be able to receive an article as it is not formatted correctly – it is missing the type, originator and org fields.
			* Client 2 will not be able to publish the article as it does not contain the type, originator and org fields
			* Neither client will receive an article


* Test Case #3: Edge Condition – We want to run our system with the maximum allowed number of clients (MAXCLIENTS) to ensure that the server is able to handle the full load of multiple clients each of which make separate requests
	* How to run:
		* Server:
			* Run the server: `./communicate_server`
		* Client 1:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> "Sports;;UMN;"
		* Client 2:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> "Sports;;;"
		* Client 3:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "5"
			* \<user enters> "Sports;;UMN;Football is truly a sport"
		* Client 4:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> "Business;;Forbes;"
		* Client 5:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "5"
			* \<user enters> "Business;;Forbes;Among the top 10 most influential people this year are Elon Musk, Jeff Bezos and Bill Gates"
		* Client 6:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> "Entertainment;Rick Astley;Youtube;"
		* Client 7:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "5"
			* \<user enters> "Entertainment;Rick Astley;Youtube;Never gonna give you up"
		* Expected results:
			* Clients 1 and 2 will receive an article published by client 3 (who does not receive anything as they have published)
			* Client 4 receives an article from client 5 (who does not receive anything as they are the publisher)
			* Client 6 receives an article from client 7 (who does not receive anything as they are the publisher)


* Test Case #4: Concurrent requests – Clients are able to make requests to the server concurrently, and the server fulfills each request (Tested with code [here](./a.py))
	* How to run:
		* Server:
			* Run the server: `./communicate_server`
		* Client 1:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "3"
			* \<user enters> "Science;;;"
			* \<user enters> "q"
		* Client 2:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "5"
			* \<user enters> "Science;;UMN;The field of Biotechnology is amazing with great breakthroughs happening daily."
			* \<user enters> "q"
		* Client 3:
			* Run the client: `./communicate_client localhost`
			* \<user enters> "1"
			* \<user enters> "2"
			* \<user enters> "q"
		* Expected results:
			* Clients 1, 2 and 3 are served concurrently. All three clients join successfully.
			* In the order they are processed (as determined by our server) client 1 successfully receives the article published by client 2
			* Client 3 joins and leaves the server without receiving any articles, and Client 2 successfully leaves once their article is published.