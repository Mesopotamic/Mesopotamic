# Vulkan 

We can't write our own graphics API, because there's no way we can write all the drivers. So instead we use the most low-level commonly available graphics API. This is so we can use proper hardware acceleration. There's a bunch of different components 

## Vulkan Headers

We parse the Vulkan registry manually to generate our own Vulkan headers, so that we don't make the user rely on having the Vulkan headers installed in the right place. This also allows us to have our own fancy tricks that we can do, such as loading extension function pointers automatically.

There are two types. Ones that will load the function pointers globally, and another that will load those functions within a structs name space. These are called **VkClay** and **VkTablet** respectively  

(Think of it as a tablet being an instance of clay)