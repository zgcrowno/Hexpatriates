#pragma once

#include "Hexpatriates.h"

namespace hexpatriates
{
    /// <summary>A wrapper for ScrollObject which serves to make ScrollObjects less procedural, and more object-oriented.</summary>
    class ScrollMod : public ScrollObject
    {
    public:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete();
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);

        /// <summary>Returns the orxSTRUCTURE, if it exists, that matches <paramref name="_structureID"/> and is associated with the ScrollMod.</summary>
        /// <param name="_structureID">The orxSTRUCTURE_ID of the structure we wish to locate within the ScrollMod.</param>
        /// <returns>The orxSTRUCTURE, if it exists, which matches <paramref name="_structureID"/> and is associated with the ScrollMod.</returns>
        orxSTRUCTURE *GetStructure(orxSTRUCTURE_ID _structureID);
        /// <summary>Returns a pointer to the ScrollMod, if it exists, which is a child of the ScrollMod, and which has the name <paramref name="_childName"/>.</summary>
        /// <param name="_childName">The name by which we're searching for a child of the ScrollMod.</param>
        /// <returns>A pointer to the ScrollMod, if it exists, which is a child of the ScrollMod, and which has the name <paramref name="_childName"/>.</returns>
        ScrollObject *GetChildByName(const orxSTRING _childName);
        /// <summary>Returns the world's gravity.</summary>
        /// <returns>The world's gravity.</returns>
        orxVECTOR GetWorldGravity();
        /// <summary>Returns a pointer to the body part, if it exists, which is a part of the ScrollMod's body, and which has the name <paramref name="_partName"/>.</summary>
        /// <param name="_partName">The name by which we're searching for a body part which is a part of the ScrollMod's body.</param>
        /// <returns>A pointer to the body part, if it exists, which is a part of the ScrollMod's body, and which has the name <paramref name="_partName"/>.</returns>
        orxBODY_PART *GetBodyPartByName(const orxSTRING &_partName);
        /// <summary>Sets the ScrollMod's custom gravity to <paramref name="_customGravity"/>.</summary>
        /// <param name="_customGravity">The gravity to which we're setting the ScrollMod's custom gravity.</param>
        void SetCustomGravity(orxVECTOR &_customGravity);
        /// <summary>Sets the body part of the ScrollMod associated with <paramref name="_partName"/>'s solidity to the bool value represented by <paramref name="_bSolid"/>.</summary>
        /// <param name="_partName">The name of the body part whose solidity we wish to set.</param>
        /// <param name="_bSolid">The bool value representing the solidity we wish to set.</param>
        void SetBodyPartSolid(const orxCHAR *_partName, const orxBOOL &_bSolid);
        /// <summary>Destroys the ScrollMod immediately.</summary>
        void Destroy();
    };
}
