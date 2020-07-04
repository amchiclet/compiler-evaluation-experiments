def get_file_contents(path):
  with open(path) as f:
    return f.read()

def set_file_contents(path, contents):
  with open(path, 'w') as f:
    return f.write(contents)
