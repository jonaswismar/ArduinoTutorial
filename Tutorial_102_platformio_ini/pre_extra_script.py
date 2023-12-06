# Import the current working construction
# environment to the `env` variable.
# alias of `env = DefaultEnvironment()`
Import("env")

# Dump construction environment (for debug purpose)
# print(env.Dump())

print("before_compile")





#
# Upload actions
#

def before_upload(source, target, env):
    print("before_upload")
    # do some actions

def after_upload(source, target, env):
    print("after_upload")
    # do some actions

env.AddPreAction("upload", before_upload)
env.AddPostAction("upload", after_upload)