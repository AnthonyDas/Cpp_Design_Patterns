#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Interface-based_Programming_(IBP)

Interface-based Programming (IBP)

Interface-based programming is closely related with Modular Programming and Object-Oriented
Programming, it defines the application as a collection of inter-coupled modules (interconnected
and which plug into each other via interface). Modules can be unplugged, replaced, or upgraded,
without the need of compromising the contents of other modules.

The total system complexity is greatly reduced. Interface Based Programming adds more to modular
Programming in that it insists that Interfaces are to be added to these modules. The entire system
is thus viewed as Components and the interfaces that helps them to co-act.

Interface-based Programming increases the modularity of the application and hence its maintainability
at a later development cycles, especially when each module must be developed by different teams.
It is a well-known methodology that has been around for a long time and it is a core technology
behind frameworks such as CORBA.

This is particularly convenient when third parties develop additional components for the established
system. They just have to develop components that satisfy the interface specified by the parent
application vendor.

Thus the publisher of the interfaces assures that he will not change the interface and the subscriber
agreesto implement the interface as whole without any deviation. An interface is therefore said to be
a Contractual agreement and the programming paradigm based on this is termed as "interface based
programming". */