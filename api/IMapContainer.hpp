/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** IMapContainer
*/

#include <string>

#pragma once

/*! \namespace Pizzia
 *
 * Namespace used for the Pizzia API
 */
namespace Pizzia {

	/*! \class IMapContainer
	 * \brief This interface class is an encapsulation of an std::unordered_map, and can be useful to store configurations.
	 */
	class IMapContainer {
	public:
		/*!
		 * \fn IMapContainer()
		 * \brief Constructor
		 * \details Constructor of the IMapContainer interface class.
		 */
		IMapContainer() = default;
		/*!
		 * \fn virtual ~IMapContainer()
		 * \brief Destructor
		 * \details Destructor of the IMapContainer interface class.
		 */
		virtual ~IMapContainer() = default;
		/*!
		 * \fn IMapContainer &operator=(const IMapContainer &)
		 * \brief Disabling the copy-assignment operator
		 * \details Disabling the copy-assignment operator '='.
		 *
		 * \return The IMapContainer you invoked upon '='.
		 */
		IMapContainer &operator=(const IMapContainer &) = delete;

	public:
		/*!
		 * \fn virtual bool create(const std::string &key, const std::string &value)
		 * \brief Create new key and value of type std::string.
		 * \details Create a new key/value (of type std::string) pair to the collection.
		 *
		 * \param key The new key to create in the collection.
		 * \param value The initial value (of type std::string) to bind with the new key.
		 * \return true if the insertion was successful, false if not.
		 */
		virtual bool create(const std::string &key, const std::string &value) = 0;
		/*!
		 * \fn virtual bool create(const std::string &key, int value)
		 * \brief Create new key and value of type int.
		 * \details Create a new key/value (of type int) pair to the collection.
		 *
		 * \param key The new key to create in the collection.
		 * \param value The initial value (of type int) to bind with the new key.
		 * \return true if the insertion was successful, false if not.
		 */
		virtual bool create(const std::string &key, int value) = 0;
		/*!
		 * \fn virtual bool create(const std::string &key, bool value)
		 * \brief Create new key and value of type bool.
		 * \details Create a new key/value (of type bool) pair to the collection.
		 *
		 * \param key The new key to create in the collection.
		 * \param value The initial value (of type bool) to bind with the new key.
		 * \return true if the insertion was successful, false if not.
		 */
		virtual bool create(const std::string &key, bool value) = 0;
		/*!
		 * \fn virtual bool create(const std::string &key, float value)
		 * \brief Create new key and value of type float.
		 * \details Create a new key/value (of type float) pair to the collection.
		 *
		 * \param key The new key to create in the collection.
		 * \param value The initial value (of type float) to bind with the new key.
		 * \return true if the insertion was successful, false if not.
		 */
		virtual bool create(const std::string &key, float value) = 0;

		/*!
		 * \fn virtual void put(const std::string &key, const std::string &value)
		 * \brief Put a new value in an already existing key.
		 * \details Replace the value in the key/value pair that is already in the collection, binding the old key to a new value (of type std::string).
		 *
		 * \param key The key that is already in the collection.
		 * \param value The new value (of type std::string) to bind with the key.
		 */
		virtual void put(const std::string &key, const std::string &value) = 0;
		/*!
		 * \fn virtual void put(const std::string &key, int value)
		 * \brief Put a new value in an already existing key.
		 * \details Replace the value in the key/value pair that is already in the collection, binding the old key to a new value (of type int).
		 *
		 * \param key The key that is already in the collection.
		 * \param value The new value (of type int) to bind with the key.
		 */
		virtual void put(const std::string &key, int value) = 0;
		/*!
		 * \fn virtual void put(const std::string &key, bool value)
		 * \brief Put a new value in an already existing key.
		 * \details Replace the value in the key/value pair that is already in the collection, binding the old key to a new value (of type bool).
		 *
		 * \param key The key that is already in the collection.
		 * \param value The new value (of type bool) to bind with the key.
		 */
		virtual void put(const std::string &key, bool value) = 0;
		/*!
		 * \fn virtual void put(const std::string &key, float value)
		 * \brief Put a new value in an already existing key.
		 * \details Replace the value in the key/value pair that is already in the collection, binding the old key to a new value (of type float).
		 *
		 * \param key The key that is already in the collection.
		 * \param value The new value (of type float) to bind with the key.
		 */
		virtual void put(const std::string &key, float value) = 0;

		/*!
		 * \fn virtual std::string getString(const std::string &key) const
		 * \brief Get the value bound to the key.
		 * \details Get the value (of type std::string) bound to the key in the collection.
		 *
		 * \param key The key that is already in the collection.
		 * \return The value (of type std::string) bounded to the key.
		 */
		virtual std::string getString(const std::string &key) const = 0;
		/*!
		 * \fn virtual int getInt(const std::string &key) const
		 * \brief Get the value bound to the key.
		 * \details Get the value (of type int) bound to the key in the collection.
		 *
		 * \param key The key that is already in the collection.
		 * \return The value (of type int) bounded to the key.
		 */
		virtual int getInt(const std::string &key) const = 0;
		/*!
		 * \fn virtual bool getBool(const std::string &key) const
		 * \brief Get the value bound to the key.
		 * \details Get the value (of type bool) bound to the key in the collection.
		 *
		 * \param key The key that is already in the collection.
		 * \return The value (of type bool) bounded to the key.
		 */
		virtual bool getBool(const std::string &key) const = 0;
		/*!
		 * \fn virtual float getFloat(const std::string &key) const
		 * \brief Get the value bound to the key.
		 * \details Get the value (of type float) bound to the key in the collection.
		 *
		 * \param key The key that is already in the collection.
		 * \return The value (of type float) bounded to the key.
		 */
		virtual float getFloat(const std::string &key) const = 0;

		/*!
		 * \fn virtual void del(const std::string &key)
		 * \brief Delete a pair from the collection.
		 * \details Remove a key/value pair from the collection, unbinding the given key from its value.
		 *
		 * \param key The key that is already in the collection.
		 */
		virtual void del(const std::string &key) = 0;

		/*!
		 * \fn virtual bool has(const std::string &key) const
		 * \brief Check if a key exists.
		 * \details Check if the key passed in parameter exists in the collection.
		 *
		 * \param key The key that is already in the collection.
		 * \return true if found, false if not.
		 */
		virtual bool has(const std::string &key) const = 0;

		/*!
		 * \fn virtual std::unordered_map<std::string, std::string>::const_iterator begin() const
		 * \brief Get an iterator to the first element of the map.
		 * \details Get an iterator to the first element of the collection (its use is the same as any other iterator from the C++ Standard Library).
		 *
		 * \return An iterator to the first element of the collection.
		 */
		virtual std::unordered_map<std::string, std::string>::const_iterator begin() const = 0;
		/*!
		 * \fn virtual std::unordered_map<std::string, std::string>::const_iterator end() const
		 * \brief Get an iterator to the last element of the map.
		 * \details Get an iterator to the last element of the collection (its use is the same as any other iterator from the C++ Standard Library).
		 *
		 * \return An iterator to the last element of the collection.
		 */
		virtual std::unordered_map<std::string, std::string>::const_iterator end() const = 0;
	};

}