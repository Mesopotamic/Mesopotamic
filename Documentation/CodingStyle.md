# Mesopotamic Coding Style

These naming conventions are most struct only on the user readable include files. So if you're not totally following this when working on internal stuff, don't worry too much. 

**Functions** : function names are all lower case and use underscores. They have the naming scheme of decreasing in scope

````c
solomon_window_start /* OKAY  */
StartSolomonWindow   /* WRONG */
SolomonWindowStart   /* WRONG */
````

 **Types** : Types naming schemes are used around creation of structs, enums and typedefs. Structs and enums should be typedef'ed. 

Types are Pascal Cased, especially those that are user accessible in headers

````c
MesoXmlEnum      /* OKAY  */
enum MesoXmlEnum /* WRONG */
meso_xml_enum    /* WRONG */
````

 **Variables**: variables are in camel case.

````c
MesoXMLNode currentNode  /* OKAY  */
MesoXMLNode CurrentNode  /* WRONG */
MesoXMLNode current_node /* WRONG */
````

