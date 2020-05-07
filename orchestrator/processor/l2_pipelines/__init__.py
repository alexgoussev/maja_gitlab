import os
import inspect
from orchestrator.modules.maja_module import MajaModule
from orchestrator.plugins.common.factory.factory_base import FactoryBase
from orchestrator.common.logger.maja_logging import configure_logger

LOGGER = configure_logger(__name__)

path = os.path.dirname(os.path.abspath(__file__))

for py in [f[:-3] for f in os.listdir(path) if f.endswith('.py') and f != '__init__.py']:
    mod = __import__('.'.join([__name__, py]), fromlist=[py])
    classes = [
        getattr(
            mod,
            x) for x in dir(mod) if (
            inspect.isclass(
                getattr(
                    mod,
                    x)) and issubclass(
                        getattr(
                            mod,
                            x),
                MajaModule)) and (
            not getattr(
                mod,
                x).__name__ == "MajaModule")]
    for cls in classes:
        FactoryBase.register(cls.NAME, cls)
