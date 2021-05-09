COEN244.Assignment(2)    Due date: Feb. 15st, 2016

Bank Service Counter 
=====================

Rough Specifications (as received from bank)
--------------------

A bank service counter has a queue of persons waiting to be served.
A bank holds a number of accounts, each having: a unique identification number (ID),
the name of the owner and a balance (which cannot be negative).
Assume there is only one service queue, and every person (waiting in line to be served) either 
has one (or more) accounts in the bank or does not have any account.
As such, once a person reaches the service counter, he is served 
by the service person (server). This person may ask for any one of the following services:
 
(a) create a new account, possibly depositing a sum of money into it;
(b) close an existing account (with ID), withdrawing any positive balance from it;
(c) deposit an amount into one of his existing accounts (with ID);
(d) withdraw an amount from one of his existing accounts (with ID)- assuming he has enough;
(e) no request.

A person can only make one request (or no request). Once a person's
request is processed by the server he leaves the line, and the next person
in line (if any) is served.

From a server's perspective, the server is simply interacting with the person 
at the front of the line and turning his request into a service 
request of the form (person_name, service_type, ID/XX, deposit/withdrawal_amount).
XX stands for a new and unique ID will have to be generated by the server. Hence,

(a) = (name, new, XX, amount)
(b) = (name, close, ID, amount)
(c) = (name, deposit, ID, amount)
(d) = (name, withdrawal, ID, amount)
(e) does not result in a service request.

A bank may be viewed as no more than a holder of accounts. Assume all accounts 
are of the same type (e.g., savings). There is no need to bunch accounts together by owner (name).
If any, the person as the front of the line is served by the server.
This may result in a service request (or none)
The result of the processing of a service request may be the creation or destruction
of a bank account or the change of some attribute of an existing account. 

Build a program that interacts with a queue of persons, processing their service requests 
in order, resulting in changes to the accounts held by the bank.


Main Program Behaviour 
----------------------

0. The program creates a bunch of accounts (on a random basis but in a way that makes sense), 
and prints them out as (name, ID, balance).

1. The program Interacts* with 'real' persons, one at a time, creating service requests that 
are added to the service requests queue. Once all the persons are handled, the result will be a queue 
of service requests that need processing.

2. The program proceeds to process one service request at a time, until the queue is empty.

3. The program will reprint the accounts as (name, ID, balance).


*By interaction, I mean using the keyboard and screen as I/O devices.


Class Design Tips
-----------------

It is suggested that you build and utilize the following classes; it is up to to you to decide 
what the exact properties of each class are and the relationship between them (and their objects).

- A bank class capable of holding many account objects (of class account)
- A service_request class, capable of generating any number of service_request objects
- A queue class capable of holding a max number of service_request objects

The queue class should be derived from a base class called container. This is to allow 
for the derivation of another class (from the same base) called stack- you don't need a stack for this assignment,
and hence, you do not need to implement any of the methods of stack.


Testing Issues
--------------

It is suggested that you test each of your classes before utilizing them in your main program.
Finally, The main program must be tested with a minimum of 10 different series of interactions
(generating 10 different queues of service requests), with the state of the bank before and after 
these interactions shown. 
Please note that you are given a lot of flexibility in terms of design and testing, as long as 
you use that flexibiliy to improve design or behaviour.


// end.

