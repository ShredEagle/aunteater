# Thoughts and theory regarding ECFS

## Data flows

Different scenarios of communications can be identified, making for different categories of data flows:

* Intra-entity static flow: long lived components on a single entity.
e.g. A solid body with forces applied resulting in a displacement of the entity.
This is modeled naturally and efficiently.

* Inter-entity static flow (static interactions): long lived components on different entities used in interaction logic.
e.g. Detecting collision between several solid bodies.
This is modeled naturally with several `families` in the same `system` (or N^2 traversal of a single `family`)

* Intra-entity event:
e.g. The `entity` is colliding at this step, it must react accordingly depending on other `components` of the entity (play a sound, lose HP, move)

* Inter-entity event:
e.g. A secondary module losing HP also decrement a main module HP.
e.g. A scenario emits a trigger, to which different `entities` will react.
