"""
Multigroup neutron and photon NDI records and subrecords
"""
from __future__ import annotations
import typing
__all__: list[str] = ['AverageFissionEnergyRelease', 'CrossSection', 'DownScatteringLegendreMoment', 'DownScatteringMatrix', 'EnergyGroupStructure', 'FissionNeutronMultiplicity', 'FissionNeutronProduction', 'FissionNeutronSpectrumMatrix', 'FissionNeutronSpectrumVector', 'FissionType', 'FluxWeights', 'HeatingNumbers', 'Kerma', 'LegendreMoment', 'Metadata', 'Multiplicities', 'OutgoingParticleTransportData', 'OutgoingParticleTypes', 'ReactionCrossSections', 'ReactionMultiplicities', 'ReactionMultiplicityType', 'ScatteringMatrix', 'TotalCrossSection', 'Velocities']
class AverageFissionEnergyRelease:
    """
    An average fission energy release record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str) -> AverageFissionEnergyRelease:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
        """
    def __init__(self, total: float, prompt: float, neutrons: float, gammas: float, betas: float, fragments: float) -> None:
        """
        Initialise the record
        
        Arguments:
            self        the record
            total       the total energy release (including delayed particles
                        and neutrinos)
            prompt      the recoverable energy release (total minus delayed
                        particles and neutrinos)
            neutrons    the energy release through prompt neutrons
            gammas      the energy release through prompt gammas
            betas       the energy release through delayed betas
            fragments   the kinetic energy of fission fragments
        """
    def to_string(self) -> str:
        """
        Return the string representation of the record
        
        Arguments:
            self    the record
        """
    @property
    def delayed_betas(self) -> float:
        """
        The energy release through delayed betas
        """
    @property
    def empty(self) -> bool:
        """
        Flag indicating whether or not the record is empty
        """
    @property
    def fission_fragments(self) -> float:
        """
        The kinetic energy of the fission products
        """
    @property
    def keyword(self) -> str:
        """
        The record keyword
        """
    @property
    def prompt_energy_release(self) -> float:
        """
        The prompt energy release (total energy release minus delayed particles
        and neutrinos)
        """
    @property
    def prompt_gammas(self) -> float:
        """
        The energy release through prompt gammas
        """
    @property
    def prompt_neutrons(self) -> float:
        """
        The kinetic energy of the prompt fission neutrons
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def total_energy_release(self) -> float:
        """
        The total energy release (including delayed particles and neutrinos)
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """
class CrossSection:
    """
    A cross section subrecord for multigroup neutron and photon data
    """
    def __init__(self, reaction: int, qvalue: float, values: list[float]) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self       the record
            reaction   the reaction number
            qvalue     the q value
            values     the cross section values
        """
    def to_string(self) -> str:
        """
        Return the string representation of the subrecord
        
        Arguments:
            self    the subrecord
        """
    @property
    def cross_sections(self) -> ...:
        """
        The cross section values
        """
    @property
    def empty(self) -> bool:
        """
        Flag indicating whether or not the subrecord is empty
        """
    @property
    def identifier(self) -> int:
        """
        The reaction identifier
        """
    @property
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def qvalue(self) -> float:
        """
        The reaction Q value
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
class DownScatteringLegendreMoment:
    """
    A Legendre moment subrecord for multigroup neutron data using an upper
    triangular matrix (deprecated)
    """
    def __init__(self, order: int, values: list[float], groups: int) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self      the record
            order     the Legendre order
            values    the compressed (down scatter) values of the matrix
            groups    the number of groups
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
    def matrix(self) -> ...:
        """
        The full matrix defined by this record
        """
    @property
    def number_groups(self) -> int:
        """
        The number of groups
        """
    @property
    def number_outgoing_groups(self) -> int:
        """
        The number of outgoing groups
        """
    @property
    def number_primary_groups(self) -> int:
        """
        The number of primary groups
        """
    @property
    def order(self) -> int:
        """
        The Legendre moment order
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
class DownScatteringMatrix:
    """
    A scattering matrix record for multigroup neutron data using upper
    triangular matrices (deprecated)
    """
    @staticmethod
    def from_string(string: str, groups: int, number: int) -> DownScatteringMatrix:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            groups    the number of energy groups
            number    the number of moments
        """
    def __init__(self, moments: list[DownScatteringLegendreMoment]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            moments   the Legendre moments of the scattering matrix
        """
    def has_moment(self, order: int) -> bool:
        """
        Return whether or not a given moment is present
        
        Arguments:
            self     the record
            order    the Legendre order to look for
        """
    def moment(self, order: int) -> DownScatteringLegendreMoment:
        """
        Return the moment for a given order
        
        Arguments:
            self     the record
            order    the Legendre order to look for
        """
    def to_scattering_matrix(self) -> ...:
        """
        Convert this deprecated record to a ScatteringMatrix instance
        
        Arguments:
            self     the record
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
    def moments(self) -> list[DownScatteringLegendreMoment]:
        """
        The Legendre moments
        """
    @property
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def number_legendre_moments(self) -> int:
        """
        The number of moments defined in this record
        """
    @property
    def number_outgoing_groups(self) -> int:
        """
        The number of outgoing groups defined by this record
        """
    @property
    def number_primary_groups(self) -> int:
        """
        The number of primary groups defined by this record
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
class EnergyGroupStructure:
    """
    A group structure record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> EnergyGroupStructure:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of boundary values to be read
        """
    @typing.overload
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the group structure boundary values
        """
    @typing.overload
    def __init__(self, particle: int, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self          the table
            particle      the secondary particle identifier
            values        the group structure boundary values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def particle(self) -> int | None:
        """
        The particle identifier
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
class FissionNeutronMultiplicity:
    """
    A fission neutron multiplicity record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> FissionNeutronMultiplicity:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of groups
        """
    def __init__(self, type: FissionType, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            type      the fission type (prompt, delayed or total)
            values    the fission neutron multiplicity values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def type(self) -> FissionType:
        """
        The fission type defined by this record
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """
class FissionNeutronProduction:
    """
    A fission neutron production record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> FissionNeutronProduction:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of groups
        """
    def __init__(self, type: FissionType, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            type      the fission type (prompt, delayed or total)
            values    the fission neutron production values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def type(self) -> FissionType:
        """
        The fission type defined by this record
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """
class FissionNeutronSpectrumMatrix:
    """
    A fission neutron spectrum matrix record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> FissionNeutronSpectrumMatrix:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of groups
        """
    def __init__(self, type: FissionType, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            type      the fission type (prompt, delayed or total)
            values    the fission neutron spectrum matrix values
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
    def matrix(self) -> ...:
        """
        The matrix defined by this record
        """
    @property
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def type(self) -> FissionType:
        """
        The fission type defined by this record
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """
class FissionNeutronSpectrumVector:
    """
    A fission neutron spectrum vector record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> FissionNeutronSpectrumVector:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of groups
        """
    def __init__(self, type: FissionType, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            type      the fission type (prompt, delayed or total)
            values    the fission neutron spectrum vector values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def type(self) -> FissionType:
        """
        The fission type defined by this record
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """
class FissionType:
    """
    The fission data types
    
    Members:
    
      Prompt
    
      Delayed
    
      Total
    """
    Delayed: typing.ClassVar[FissionType]  # value = <FissionType.Delayed: 2>
    Prompt: typing.ClassVar[FissionType]  # value = <FissionType.Prompt: 1>
    Total: typing.ClassVar[FissionType]  # value = <FissionType.Total: 3>
    __members__: typing.ClassVar[dict[str, FissionType]]  # value = {'Prompt': <FissionType.Prompt: 1>, 'Delayed': <FissionType.Delayed: 2>, 'Total': <FissionType.Total: 3>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
class FluxWeights:
    """
    A flux weight record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> FluxWeights:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of weight values to be read
        """
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the flux weight values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
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
class HeatingNumbers:
    """
    A heating numbers record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> HeatingNumbers:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of heating numbers to be read
        """
    @typing.overload
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the heating numbers
        """
    @typing.overload
    def __init__(self, particle: int, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self        the table
            particle    the secondary particle identifier
            values      the heating numbers
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def particle(self) -> int | None:
        """
        The particle identifier
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
class Kerma:
    """
    A kerma record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> Kerma:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of kerma values to be read
        """
    @typing.overload
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the kerma values
        """
    @typing.overload
    def __init__(self, particle: int, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self        the table
            particle    the secondary particle identifier
            values      the kerma values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def particle(self) -> int | None:
        """
        The particle identifier
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
class LegendreMoment:
    """
    A Legendre moment subrecord for multigroup neutron and photon data
    """
    @typing.overload
    def __init__(self, order: int, values: list[float], incident: int) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self        the record
            order       the Legendre order
            values      the values of the matrix
            incident    the number of primary groups
        """
    @typing.overload
    def __init__(self, order: int, values: list[float], incident: int, outgoing: int) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self        the record
            order       the Legendre order
            values      the values of the matrix
            incident    the number of primary groups
            outgoing    the number of outgoing groups
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
    def matrix(self) -> ...:
        """
        The matrix defined by this subrecord
        """
    @property
    def number_outgoing_groups(self) -> int:
        """
        The number of outgoing groups
        """
    @property
    def number_primary_groups(self) -> int:
        """
        The number of incident groups
        """
    @property
    def order(self) -> int:
        """
        The Legendre moment order
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
class Metadata:
    """
    A group Metadata record for multigroup neutron and photon data
    """
    def __init__(self, zaid: str, libname: str, process: str, awr: float, temperature: float, dilution: float, groups: int, reactions: int, legendre: int, outgoing_groups: dict[int, int] = {}, outgoing_legendre: dict[int, int] = {}, information: str | None = None, source: str | None = None, weight: float | None = None, upscatter: int | None = None, downscatter: int | None = None) -> None:
        """
        Initialise the record
        
        Arguments:
            self                the metadata
            zaid                the zaid of the table
            libname             the library name
            process             the processing date
            awr                 the atomic weight ratio of the target (with respect
                                to the neutron mass)
            temperature         the temperature of the target
            dilution            the dilution (aka sigma0)
            groups              the number of groups in the primary group structure
            reactions           the number of reactions defined in the table
            legendre            the number of Legendre moments in the table
            outgoing_group      the number of groups in the outgoing group structures (optional)
            outgoing_legendre   the number of groups in the outgoing group structures (optional)
            information         the table information line (optional)
            source              the source date (optional)
            weight              the atomic weight of the target (optional)
            upscatter           the number of upscatter groups (optional)
            downscatter         the number of downscatter groups (optional)
        """
    def number_outgoing_groups(self, particle: int) -> int | None:
        """
        The number of outgoing groups defined by this record for the particle
        
        Arguments:
            self       the metadata
            particle   the outgoing particle identifier
        """
    def number_outgoing_legendre_moments(self, particle: int) -> int | None:
        """
        The number of outgoing Legendre moments defined by this recordArguments:
            self       the metadata
            particle   the outgoing particle identifier
        """
    def to_string(self) -> str:
        """
        Return the string representation of the subrecord
        
        Arguments:
            self    the metadata
        """
    @property
    def atomic_weight(self) -> float | None:
        """
        The atomic weight of the target
        """
    @property
    def atomic_weight_ratio(self) -> float | None:
        """
        The atomic weight ratio of the target (with respect to the neutron mass)
        """
    @property
    def dilution(self) -> float | None:
        """
        The dilution (aka sigma0)
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
    def number_downscatter_groups(self) -> int | None:
        """
        The number of downscatter groups defined by this record
        """
    @property
    def number_groups(self) -> int | None:
        """
        The number of groups defined by this record
        """
    @property
    def number_legendre_moments(self) -> int | None:
        """
        The number of Legendre moments defined by this record
        """
    @property
    def number_outgoing_particles(self) -> int | None:
        """
        The number of outgoing particles by this record
        """
    @property
    def number_reactions(self) -> int | None:
        """
        The number of reactions defined by this record
        """
    @property
    def number_upscatter_groups(self) -> int | None:
        """
        The number of upscatter groups defined by this record
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
    def temperature(self) -> float | None:
        """
        The temperature of the target
        """
    @property
    def zaid(self) -> str | None:
        """
        The zaid of the table
        """
class Multiplicities:
    """
    A reaction product multiplicity subrecord for multigroup data
    """
    def __init__(self, reaction: int, products: list[int], multiplicities: list[int]) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self              the record
            reaction          the reaction number
            products          the reaction product identifiers
            multiplicities    the multiplicity values
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
    def identifier(self) -> int:
        """
        The reaction identifier
        """
    @property
    def multiplicities(self) -> ...:
        """
        The reaction product multiplicities
        """
    @property
    def number_reaction_products(self) -> int:
        """
        The number of reaction products
        """
    @property
    def reaction_products(self) -> ...:
        """
        The reaction product identifiers
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
class OutgoingParticleTransportData:
    """
    An outgoing particle transport data record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> OutgoingParticleTransportData:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of zaid values to be read
        """
    def __init__(self, values: list[str]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the zaid values
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
    def number_outgoing_particles(self) -> int:
        """
        The number of outgoing particles defined by this record
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
class OutgoingParticleTypes:
    """
    An outgoing particle type record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> OutgoingParticleTypes:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of particle types to be read
        """
    def __init__(self, values: list[int]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the particle types
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
    def number_outgoing_particles(self) -> int:
        """
        The number of outgoing particles defined by this record
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
class ReactionCrossSections:
    """
    A reaction cross section record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, reactions: int, groups: int) -> ReactionCrossSections:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string      the string representing the record
            reactions   the number of reactions to be read
            groups      the number of groups to be read
        """
    def __init__(self, xs: list[CrossSection]) -> None:
        """
        Initialise the record
        
        Arguments:
            self   the record
            xs     the cross section data
        """
    def has_reaction(self, reaction: int) -> bool:
        """
        Return whether or not a given reaction is present
        
            self        the record
            reaction    the reaction to look for
        """
    def reaction(self, reaction: int) -> CrossSection:
        """
        Return the cross section data for a given reaction
        
            self        the record
            reaction    the reaction to look for
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions defined by this record
        """
    @property
    def reactions(self) -> list[CrossSection]:
        """
        The cross section data for all reactions
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
class ReactionMultiplicities:
    """
    A reaction product multiplicity record for multigroup data
    """
    @staticmethod
    def from_string(string: str, reactions: int) -> ReactionMultiplicities:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string      the string representing the record
            reactions   the number of reactions to be read
        """
    @typing.overload
    def __init__(self, multiplicities: list[Multiplicities]) -> None:
        """
        Initialise the record
        
        Arguments:
            self              the record
            multiplicities    the multiplicity data
        """
    @typing.overload
    def __init__(self, type: ReactionMultiplicityType, multiplicities: list[Multiplicities]) -> None:
        """
        Initialise the record
        
        Arguments:
            self              the record
            type              the multiplicity type (all, few or rmo)
            multiplicities    the multiplicity data
        """
    def has_reaction(self, reaction: int) -> bool:
        """
        Return whether or not a given reaction is present
        
            self        the record
            reaction    the reaction to look for
        """
    def reaction(self, reaction: int) -> Multiplicities:
        """
        Return the multiplicity data for a given reaction
        
            self        the record
            reaction    the reaction to look for
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
    def number_reactions(self) -> int:
        """
        The number of reactions defined by this record
        """
    @property
    def reactions(self) -> list[Multiplicities]:
        """
        The multiplicity data for all reactions
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def type(self) -> ReactionMultiplicityType | None:
        """
        The multiplicity type defined by this record
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """
class ReactionMultiplicityType:
    """
    The reaction multiplicity types
    
    Members:
    
      All
    
      Few
    
      RMO
    """
    All: typing.ClassVar[ReactionMultiplicityType]  # value = <ReactionMultiplicityType.All: 1>
    Few: typing.ClassVar[ReactionMultiplicityType]  # value = <ReactionMultiplicityType.Few: 2>
    RMO: typing.ClassVar[ReactionMultiplicityType]  # value = <ReactionMultiplicityType.RMO: 3>
    __members__: typing.ClassVar[dict[str, ReactionMultiplicityType]]  # value = {'All': <ReactionMultiplicityType.All: 1>, 'Few': <ReactionMultiplicityType.Few: 2>, 'RMO': <ReactionMultiplicityType.RMO: 3>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
class ScatteringMatrix:
    """
    A scattering matrix record for multigroup neutron and photon data
    """
    @staticmethod
    @typing.overload
    def from_string(string: str, incident: int, number: int) -> ScatteringMatrix:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string      the string representing the record
            incident    the number of incident energy groups
            number      the number of moments
        """
    @staticmethod
    @typing.overload
    def from_string(string: str, incident: int, outgoing: int, number: int) -> ScatteringMatrix:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string      the string representing the record
            incident    the number of incident energy groups
            outgoing    the number of outgoing energy groups
            number      the number of moments
        """
    @typing.overload
    def __init__(self, moments: list[LegendreMoment]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            moments   the Legendre moments of the scattering matrix
        """
    @typing.overload
    def __init__(self, particle: int, moments: list[LegendreMoment]) -> None:
        """
        Initialise the record
        
        Arguments:
            self       the record
            particle   the secondary particle identifier
            moments    the Legendre moments of the scattering matrix
        """
    def has_moment(self, order: int) -> bool:
        """
        Return whether or not a given moment is present
        
            self     the record
            order    the Legendre order to look for
        """
    def moment(self, order: int) -> LegendreMoment:
        """
        Return the moment for a given order
        
            self     the record
            order    the Legendre order to look for
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
    def moments(self) -> list[LegendreMoment]:
        """
        The  Legendre moments
        """
    @property
    def number_legendre_moments(self) -> int:
        """
        The number of moments defined in this record
        """
    @property
    def number_outgoing_groups(self) -> int:
        """
        The number of outgoing groups defined by this record
        """
    @property
    def number_primary_groups(self) -> int:
        """
        The number of primary groups defined by this record
        """
    @property
    def particle(self) -> int | None:
        """
        The particle identifier
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
class TotalCrossSection:
    """
    A total cross section record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> TotalCrossSection:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of cross section values to be read
        """
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the total cross section values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
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
class Velocities:
    """
    A velocity record for multigroup neutron and photon data
    """
    @staticmethod
    def from_string(string: str, number: int) -> Velocities:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of velocity values to be read
        """
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the velocity values
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
    def number_groups(self) -> int:
        """
        The number of groups defined by this record
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
