#pragma once

#include "Hexpatriates.h"
#include <map>
#include <vector>

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

        /// <summary>A variation on Hexpatriates' CreateObject function which allows the passage of config-appropriate parameters.</summary>
        /// <param name="_modelName">The name of the model we wish to instantiate.</param>
        /// <param name="_boolParamMap">The bool parameters we wish to pass.</param>
        /// <param name="_floatParamMap">The float parameters we wish to pass.</param>
        /// <param name="_vectorParamMap">The vector parameters we wish to pass.</param>
        /// <param name="_stringParamMap">The string parameters we wish to pass.</param>
        /// <returns>The freshly constructed ScrollMod instance.</returns>
        ScrollMod *CreateObject(
            const orxCHAR *_modelName,
            std::map<const orxCHAR*, const orxBOOL> _boolParamMap = {},
            std::map<const orxCHAR*, const orxFLOAT> _floatParamMap = {},
            std::map<const orxCHAR*, const orxVECTOR*> _vectorParamMap = {},
            std::map<const orxCHAR*, const orxSTRING> _stringParamMap = {});
        /// <summary>Gets a bool value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</summary>
        /// <param name="_key">The name of the bool we wish to retrieve from config.</param>
        /// <param name="_sectionName">The section, if any, from which we wish to retrieve <paramref name="_key"/>.</param>
        /// <returns>The bool value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</returns>
        orxBOOL __fastcall GetBool(const orxCHAR *_key, const orxCHAR *_sectionName = "");
        /// <summary>Gets a float value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</summary>
        /// <param name="_key">The name of the float we wish to retrieve from config.</param>
        /// <param name="_sectionName">The section, if any, from which we wish to retrieve <paramref name="_key"/>.</param>
        /// <returns>The float value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</returns>
        orxFLOAT __fastcall GetFloat(const orxCHAR *_key, const orxCHAR *_sectionName = "");
        /// <summary>Gets a vector value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</summary>
        /// <param name="_key">The name of the vector we wish to retrieve from config.</param>
        /// <param name="_passedVector">The vector to hold the value we're retrieving.</param>
        /// <param name="_sectionName">The section, if any, from which we wish to retrieve <paramref name="_key"/>.</param>
        /// <returns>The vector value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</returns>
        orxVECTOR *__fastcall GetVector(const orxCHAR *_key, orxVECTOR *_passedVector, const orxCHAR *_sectionName = "");
        /// <summary>Gets a string value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</summary>
        /// <param name="_key">The name of the string we wish to retrieve from config.</param>
        /// <param name="_sectionName">The section, if any, from which we wish to retrieve <paramref name="_key"/>.</param>
        /// <returns>The string value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) from config.</returns>
        const orxCHAR *__fastcall GetString(const orxCHAR *_key, const orxCHAR *_sectionName = "");
        /// <summary>Sets a bool value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) to <paramref name="_value"/>.</summary>
        /// <param name="_key">The name of the bool we wish to set in config.</param>
        /// <param name="_value">The value to which we're setting the bool named <paramref name="_key"/>.</param>
        /// <param name="_sectionName">The section, if any, in which we wish to set <paramref name="_key"/>.</param>
        /// <returns>An orxSTATUS code.</returns>
        orxSTATUS __fastcall SetBool(const orxCHAR *_key, orxBOOL _value, const orxCHAR *_sectionName = "");
        /// <summary>Sets a float value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) to <paramref name="_value"/>.</summary>
        /// <param name="_key">The name of the float we wish to set in config.</param>
        /// <param name="_value">The value to which we're setting the float named <paramref name="_key"/>.</param>
        /// <param name="_sectionName">The section, if any, in which we wish to set <paramref name="_key"/>.</param>
        /// <returns>An orxSTATUS code.</returns>
        orxSTATUS __fastcall SetFloat(const orxCHAR *_key, orxFLOAT _value, const orxCHAR *_sectionName = "");
        /// <summary>Sets a vector value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) to <paramref name="_value"/>.</summary>
        /// <param name="_key">The name of the vector we wish to set in config.</param>
        /// <param name="_value">The value to which we're setting the vector named <paramref name="_key"/>.</param>
        /// <param name="_sectionName">The section, if any, in which we wish to set <paramref name="_key"/>.</param>
        /// <returns>An orxSTATUS code.</returns>
        orxSTATUS __fastcall SetVector(const orxCHAR *_key, const orxVECTOR *_value, const orxCHAR *_sectionName = "");
        /// <summary>Sets a string value named <paramref name="_key"/> (and optionally associated with the section named <paramref name="_sectionName"/>) to <paramref name="_value"/>.</summary>
        /// <param name="_key">The name of the string we wish to set in config.</param>
        /// <param name="_value">The value to which we're setting the string named <paramref name="_key"/>.</param>
        /// <param name="_sectionName">The section, if any, in which we wish to set <paramref name="_key"/>.</param>
        /// <returns>An orxSTATUS code.</returns>
        orxSTATUS __fastcall SetString(const orxCHAR *_key, const orxCHAR *_value, const orxCHAR *_sectionName = "");
        /// <summary>Returns the orxSTRUCTURE, if it exists, that matches <paramref name="_structureID"/> and is associated with the ScrollMod.</summary>
        /// <param name="_structureID">The orxSTRUCTURE_ID of the structure we wish to locate within the ScrollMod.</param>
        /// <returns>The orxSTRUCTURE, if it exists, which matches <paramref name="_structureID"/> and is associated with the ScrollMod.</returns>
        orxSTRUCTURE *GetStructure(orxSTRUCTURE_ID _structureID);
        /// <summary>Returns a pointer to the ScrollObject, if it exists, which is a child of the ScrollMod, and which has the name <paramref name="_childName"/>.</summary>
        /// <param name="_childName">The name by which we're searching for a child of the ScrollMod.</param>
        /// <returns>A pointer to the ScrollMod, if it exists, which is a child of the ScrollMod, and which has the name <paramref name="_childName"/>.</returns>
        ScrollObject *GetChildByName(const orxSTRING _childName);
        /// <summary>Returns a pointer to the ScrollObject, if it exists, which is a child of the ScrollMod, and which has a name contained within <paramref name="_childNameList"/>.</summary>
        /// <param name="_childName">The names by which we're searching for a child of the ScrollMod.</param>
        /// <returns>A pointer to the ScrollObject, if it exists, which is a child of the ScrollMod, and which has a name contained within <paramref name="_childNameList"/>.</returns>
        ScrollObject *GetChildByName(const std::vector<orxSTRING> &_childNameList);
        /// <summary>Returns the world's gravity.</summary>
        /// <returns>The world's gravity.</returns>
        orxVECTOR GetWorldGravity();
        /// <summary>Returns a pointer to the body part, if it exists, which is a part of the ScrollMod's body, and which has the name <paramref name="_partName"/>.</summary>
        /// <param name="_partName">The name by which we're searching for a body part which is a part of the ScrollMod's body.</param>
        /// <returns>A pointer to the body part, if it exists, which is a part of the ScrollMod's body, and which has the name <paramref name="_partName"/>.</returns>
        orxBODY_PART *GetBodyPartByName(const orxCHAR *_partName);
        /// <summary>Sets the ScrollMod's target animation to <paramref name="_animName"/>.</summary>
        /// <param name="_animName">The animation to which we're setting the ScrollMod's target animation.</param>
        void SetTargetAnim(const orxCHAR *_animName);
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
