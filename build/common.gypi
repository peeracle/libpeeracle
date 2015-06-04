{
  'variables': {
    'java_home%': '<!(python -c "import os; dir=os.getenv(\'JAVA_HOME\', \'/usr/lib/jvm/java-7-openjdk-amd64\'); print dir if os.path.exists(os.path.join(dir, \'include/jni.h\')) else 0")',
  },
  'target_defaults': {
    'defines': [
      'LIBPEERACLE_REVISION="<!(git describe --tag --always)"',
    ],
    'include_dirs': [
      '<(DEPTH)',
    ],
    'conditions': [
      ['GENERATOR != "msvs"', {
        'rules': [
          {
            'rule_name': 'lint_cc',
            'extension': 'cc',
            'inputs': [
              '<(DEPTH)/third_party/cpplint/cpplint.py',
            ],
            'outputs': [
              '>(INTERMEDIATE_DIR)/<(RULE_INPUT_NAME).lintstamp',
            ],
            'conditions': [
              ['OS == "win"', {
                'action': [
                  'python', '>(_inputs)', '<!(python <(DEPTH)\\scripts\\get_current_dir.py)\\<(RULE_INPUT_PATH)'
                ],
              }, {
                'action': [
                  'python', '>(_inputs)', '$$(pwd)/<(RULE_INPUT_PATH)'
                ],
              }],
            ],
          },
          {
            'rule_name': 'lint_h',
            'extension': 'h',
            'inputs': [
              '<(DEPTH)/third_party/cpplint/cpplint.py',
            ],
            'outputs': [
              '>(INTERMEDIATE_DIR)/<(RULE_INPUT_NAME).lintstamp',
            ],
            'conditions': [
              ['OS == "win"', {
                'action': [
                  'python', '>(_inputs)', '<!(python <(DEPTH)\\scripts\\get_current_dir.py)\\<(RULE_INPUT_PATH)'
                ],
                }, {
                'action': [
                  'python', '>(_inputs)', '$$(pwd)/<(RULE_INPUT_PATH)'
                ],
              }],
            ],
          },
        ],
      }],
    ],
  },
}