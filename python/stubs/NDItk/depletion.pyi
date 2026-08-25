"""
Depletion NDI records and subrecords
"""
from __future__ import annotations
import typing
__all__: list[str] = ['IncidentParticle', 'Metadata', 'Multiplicities', 'Product', 'Target']
class IncidentParticle:
    """
    An incident particle record for depletion data
    """
    def __init__(self, identifier: int, targets: list[Target]) -> None:
        """
        Initialise the record
        
        Arguments:
            self              the record
            identifier        the target particle identifier    targets           a vector of depletion targets
        """
    def to_string(self) -> str:
        """
        Return the string representation of the record
        
        Arguments:
            self    the record
        """
    @property
    def incident_identifier(self) -> int:
        """
        Return the target particle identifier
        """
    @property
    def keyword(self) -> str:
        """
        The record keyword
        """
    @property
    def number_targets(self) -> int:
        """
        Return the number of targets for this incident particle
        """
    @property
    def targets(self) -> list[Target]:
        """
        Return the target data for this incident particle
        """
class Metadata:
    """
    A group Metadata record for depletion data
    """
    def __init__(self, zaid: str, libname: str, process: str, incident: int, information: str | None = None, source: str | None = None) -> None:
        """
        Initialise the record
        
        Arguments:
            self                the metadata
            zaid                the zaid of the table
            libname             the library name
            process             the processing date
            incident            the number of incident particles
            information         the table information line (optional)
            source              the source date (optional)
        """
    def to_string(self) -> str:
        """
        Return the string representation of the subrecord
        
        Arguments:
            self    the metadata
        """
    @property
    def information(self) -> str | None:
        """
        The table information line
        """
    @property
    def library_name(self) -> str | None:
        """
        The library name
        """
    @property
    def number_incident_particles(self) -> int | None:
        """
        The number of incident particles
        """
    @property
    def processing_date(self) -> str | None:
        """
        The process date
        """
    @property
    def source_date(self) -> str | None:
        """
        The source date
        """
    @property
    def zaid(self) -> str | None:
        """
        The zaid of the table
        """
class Multiplicities:
    """
    A reaction product multiplicity subrecord for depletion data
    """
    def __init__(self, product: int, reactions: list[int], multiplicities: list[int]) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self             the record
            product          the reaction product identifier
            reactions        the reaction identifiers
            multiplicities   the multiplicity values
        """
    def to_string(self) -> str:
        """
        Return the string representation of the subrecord
        
        Arguments:
            self    the subrecord
        """
    @property
    def empty(self) -> bool:
        """
        Flag indicating whether or not the subrecord is empty
        """
    @property
    def multiplicities(self) -> ...:
        """
        Return the reaction product multiplicities
        """
    @property
    def number_reactions(self) -> int:
        """
        Return the number of reaction identifiers
        """
    @property
    def reaction_identifiers(self) -> ...:
        """
        Return the reaction product identifiers
        """
    @property
    def reaction_product(self) -> int:
        """
        Return the reaction product identifier
        """
    @property
    def size(self) -> int:
        """
        The size of the subrecord
        """
    @property
    def values(self) -> ...:
        """
        The data values of the subrecord
        """
class Product:
    """
    A product record for depletion data
    """
    def __init__(self, multiplicities: Multiplicities) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self              the record
            multiplicities    a depletion::Multiplicities SubListRecord
        """
    def to_string(self) -> str:
        """
        Return the string representation of the record
        
        Arguments:
            self    the record
        """
    @property
    def empty(self) -> bool:
        """
        Flag indicating whether or not the record is empty
        """
    @property
    def keyword(self) -> str:
        """
        The record keyword
        """
    @property
    def multiplicities(self) -> ...:
        """
        Return the reaction multiplicities
        """
    @property
    def number_reactions(self) -> int:
        """
        Return the number of reactions with this product
        """
    @property
    def reaction_identifiers(self) -> ...:
        """
        Return the reaction identifiers
        """
    @property
    def reaction_product(self) -> int:
        """
        Return the reaction product identifier
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """
class Target:
    """
    A target record for depletion data
    """
    def __init__(self, identifier: int, products: list[Product]) -> None:
        """
        Initialise the record
        
        Arguments:
            self              the record
            identifier        the target particle identifier    products          a vector of depletion products
        """
    def to_string(self) -> str:
        """
        Return the string representation of the record
        
        Arguments:
            self    the record
        """
    @property
    def keyword(self) -> str:
        """
        The record keyword
        """
    @property
    def number_products(self) -> int:
        """
        Return the number of products for this target
        """
    @property
    def products(self) -> list[Product]:
        """
        Return the product data for this target
        """
    @property
    def target_identifier(self) -> int:
        """
        Return the target particle identifier
        """
