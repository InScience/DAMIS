from piston.handler import BaseHandler
from damis.models import Dataset


class DatasetHandler(BaseHandler):
    allowed_methods = ('GET',)
    model = Dataset
