from flask import Flask
from flask_restx import Api
from utils.controller.kl_reception import KLtxt
from utils.controller.status import ServerStatus
from utils.logs.logger import get_logger

app = Flask(__name__)
api = Api(app)

logger = get_logger(__name__)


api.add_resource(ServerStatus, '/status')
api.add_resource(KLtxt, '/txt')

if __name__ == '__main__':
    # Run the Flask app on your IP address
    app.run(host='192.168.1.72', port=5000)
