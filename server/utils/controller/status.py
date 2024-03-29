from flask_restx import Resource

class ServerStatus(Resource):
    def get(self):
        return {'message': 'Up!'},200



