# StructuredRecordsIOExample


This is a toy library to do IO on a hierarchy of kinds of records. The goal is to use C++11 features to avoid massive boilerplate code.

This library will implement the following tow scenario:

We have several kinds of items. Each kind has a correponding class that knows how it can be serialized and deserilalized. Each item has seveal properties and the set of properties is different for each kind.

Serialization and deserialization are different depending on the verison of format that is declared at the top.
