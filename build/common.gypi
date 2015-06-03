{
  'variables': {
    'java_home%': '<!(python -c "import os; dir=os.getenv(\'JAVA_HOME\', \'/usr/lib/jvm/java-7-openjdk-amd64\'); print dir if os.path.exists(os.path.join(dir, \'include/jni.h\')) else 0")',
  },
  'target_defaults': {
    'defines': [
      'LIBPEERACLE_REVISION="<!(git describe --tag --always)"',
    ],
  },
}