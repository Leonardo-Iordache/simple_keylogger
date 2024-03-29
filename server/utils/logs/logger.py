import logging
import os

def get_logger(name):
    current_dir = os.path.dirname(__file__)
    logger = logging.getLogger(name)
    logger.setLevel(logging.INFO)
    formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    file_handler = logging.FileHandler(f'{current_dir}/server.log')
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)
    return logger
