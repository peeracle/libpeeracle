{
  'includes': [
    'build/common.gypi'
  ],
  'target_defaults': {
    'defines': [
      'LIBPEERACLE_REVISION="<!(git describe --tag --always)"',
    ],
    'rules': [
      {
        'rule_name': 'lint_cc',
        'extension': 'cc',
        'inputs': [
          '<(DEPTH)/scripts/cpplint.py',
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
          '<(DEPTH)/scripts/cpplint.py',
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
    'conditions': [
      ['coverage==1 and OS=="linux"', {
        'cflags': [
          '--coverage'
        ],
        'ldflags': [
          '--coverage'
        ],
      }],
    ],
  },
}