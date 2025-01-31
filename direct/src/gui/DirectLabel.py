"""Contains the DirectLabel class.

See the :ref:`directlabel` page in the programming manual for a more in-depth
explanation and an example of how to use this class.
"""

__all__ = ['DirectLabel']

from panda3d.core import *
from .DirectFrame import *


class DirectLabel(DirectFrame):
    """
    DirectLabel(parent) - Create a DirectGuiWidget which has multiple
    states.  User explicitly chooses a state to display
    """

    def __init__(self, parent=None, **kw):
        # Inherits from DirectFrame
        # A Direct Frame can have:
        # - A background texture (pass in path to image, or Texture Card)
        # - A midground geometry item (pass in geometry)
        # - A foreground text Node (pass in text string or Onscreen Text)
        # For a direct label:
        # Each label has 1 or more states
        # The same image/geom/text can be used for all states or each
        # state can have a different text/geom/image
        # State transitions happen under user control

        optiondefs = (
            # Define type of DirectGuiWidget
            ('pgFunc',          PGItem,    None),
            ('numStates',       1,         None),
            ('state',           self.inactiveInitState, None),
            ('activeState',     0,         self.set_active_state),
        )
        # Merge keyword options with default options
        self.defineoptions(kw, optiondefs)

        # Initialize superclasses
        DirectFrame.__init__(self, parent)

        # Call option initialization functions
        self.initialiseoptions(DirectLabel)

    def set_active_state(self):
        """ set_active_state - change label to specifed state """
        self.guiItem.setState(self['activeState'])
