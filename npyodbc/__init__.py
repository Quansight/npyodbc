import sys
from types import ModuleType

from . import _npyodbc
from ._npyodbc import *  # noqa: F403

# Since the underlying _npyodbc module has a few configuration options that it
# reads on itself, and because `pyodbc` exposed these to the user, we need to pass those
# configuration options along to preserve the API. See
# https://docs.python.org/3/reference/datamodel.html#module.__class__ for the approach
# used here.

class _ProxyPyodbcModule(ModuleType):
    def __setattr__(self, name, value):  # noqa: ANN001
        _npyodbc.__setattr__(name, value)

    def __getattribute__(self, name):  # noqa: ANN001
        return _npyodbc.__getattribute__(name)

sys.modules[__name__].__class__ = _ProxyPyodbcModule
