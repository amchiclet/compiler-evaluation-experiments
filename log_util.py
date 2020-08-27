from loguru import logger
import sys
import os

def init_logger(log_file_path, replace=False):
    if os.path.exists(log_file_path):
        if replace:
            os.remove(log_file_path)
        else:
            raise RuntimeError(f'Log file {log_file_path} exists')
    logger.remove()
    logger.add(sys.stdout, level='INFO')
    logger.add(sink = log_file_path,
               level = 'DEBUG',
               format = ('{process.name} | '
                         '{time:YYYYMMDD_HH:mm:ss.SSS} | '
                         '{file}:{function}:{line} | '
                         '{message}'),
               enqueue = True)
