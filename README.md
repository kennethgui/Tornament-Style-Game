In this ongoing data structures project, the initial phase focuses on setting up a role-playing game using GitHub Classroom, introducing version control practices. The primary task involves implementing the Character class, laying the foundation for subsequent developments. The project employs inheritance, where four new classes (Mages, Scoundrels, Rangers, Barbarians) are derived from the Character class, each incorporating additional attributes and methods specific to their roles.

Moving forward, the Tavern class is introduced, functioning as a subclass of ArrayBag to hold Character objects. This involves utilizing array-based storage structures, such as ArrayBag, to efficiently manage Characters within the game setting.

The second phase introduces functionality for Characters to consume Tainted Stew, affecting each subclass uniquely. This modification necessitates adjustments to the Character class and its subclasses, employing polymorphism to handle diverse reactions to the Tainted Stew. Technical aspects like polymorphism and subclass-specific actions are crucial in implementing this feature.

Simultaneously, the Tavern class undergoes further development to accommodate storing Character subclasses polymorphically. This involves employing polymorphism in combination with array-based structures to handle diverse character types within the Tavern setting.

The ongoing project progresses to introduce the Quest struct and QuestList class. The Quest struct is implemented within the interface of the QuestList class, which is designed to store pointers to Quest objects. The QuestList class, functioning as a subclass of DoublyLinkedList, leverages linked list structures to manage personalized Quests for Characters. The project involves rigorous testing of the QuestList class using the provided debug file (debug.csv), ensuring seamless integration of Quest management functionality within the game framework.