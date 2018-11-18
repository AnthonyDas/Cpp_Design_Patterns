#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Model-View-Controller_(MVC)

Model-View-Controller (MVC)

A pattern often used by applications that need the ability to maintain multiple views of 
the same data. The model-view-controller pattern was until recently a very common pattern
especially for graphic user interlace programming, it splits the code in 3 pieces.
The model, the view, and the controller.

The Model is the actual data representation (for example, Array vs Linked List) or other
objects representing a database. The View is an interface to reading the model or a fat
client GUI. The Controller provides the interface of changing or modifying the data, and
then selecting the "Next Best View" (NBV).

Newcomers will probably see this "MVC" model as wasteful, mainly because you are working
with many extra objects at runtime, when it seems like one giant object will do. But the
secret to the MVC pattern is not writing the code, but in maintaining it, and allowing 
people to modify the code without changing much else. Also, keep in mind, that different
developers have different strengths and weaknesses, so team building around MVC is easier.
Imagine a View Team that is responsible for great views, a Model Team that knows a lot
about data, and a Controller Team that see the big picture of application flow, handing
requests, working with the model, and selecting the most appropriate next view for that
client.

For example: A naive central database can be organized using only a "model", for example,
a straight array. However, later on, it may be more applicable to use a linked list. All
array accesses will have to be remade into their respective Linked List form (for example,
you would change myarray[5] into mylist.at(5) or whatever is equivalent in the language
you use).

Well, if we followed the MVC pattern, the central database would be accessed using some
sort of a function, for example, myarray.at(5). If we change the model from an array to
a linked list, all we have to do is change the view with the model, and the whole program
is changed. Keep the interface the same but change the underpinnings of it. This would
allow us to make optimizations more freely and quickly than before.

One of the great advantages of the Model-View-Controller Pattern is obviously the ability
to reuse the application's logic (which is implemented in the model) when implementing a
different view. A good example is found in web development, where a common task is to
implement an external API inside of an existing piece of software. If the MVC pattern has
cleanly been followed, this only requires modification to the controller, which can have
the ability to render different types of views dependent on the content type requested by
the user agent. */