/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include "HttpTypes.h"
#include <sstream>

namespace HttpRequestor
{
    /*
    **
    **  The Parameters needed to make a HTTP call and then receive the
    **  returned TEXT from the web request without parsing it.
    **
    */

    class TextParameters
    {
    public:
        // Initializing ctor
        TextParameters(const AZStd::string& URI, Aws::Http::HttpMethod method, const TextCallback& callback);
        TextParameters(const AZStd::string& URI, Aws::Http::HttpMethod method, const Headers& headers, const TextCallback& callback);
        TextParameters(const AZStd::string& URI, Aws::Http::HttpMethod method, const Headers& headers, const AZStd::string& body, const TextCallback& callback);

        // Defaults
        ~TextParameters() = default;
        TextParameters(const TextParameters&) = default;
        TextParameters& operator=(const TextParameters&) = default;

        // VS2013 won't default these
        TextParameters(TextParameters&&);
        TextParameters& operator=(TextParameters&&);

        //returns the URI in string form as an recipient of the HTTP connection
        const Aws::String& GetURI() const { return m_URI; }

        //returns the method of which the HTTP request will take. GET, POST, DELETE, PUT, or HEAD
        Aws::Http::HttpMethod GetMethod() const { return m_method; }

        //returns the list of extra headers to include in the request
        const Headers & GetHeaders() const { return m_headers; }

        //returns the stream for the body of the request
        const std::shared_ptr<std::stringstream> & GetBodyStream() const { return m_bodyStream; }

        //returns the function of which to feed back the TEXT that the HTTP call resulted in. The function also requires the HTTPResponseCode indicating if the call was successful or failed
        const TextCallback & GetCallback() const { return m_callback; }

    private:
        Aws::String                             m_URI;
        Aws::Http::HttpMethod                   m_method;
        Headers                                 m_headers;
        std::shared_ptr<std::stringstream>      m_bodyStream;
        TextCallback                            m_callback;
    };
    
    inline TextParameters::TextParameters(const AZStd::string& URI, Aws::Http::HttpMethod method, const TextCallback& callback)
        : m_URI(URI.c_str())
        , m_method(method)
        , m_callback(callback)
    {
    }

    inline TextParameters::TextParameters(const AZStd::string& URI, Aws::Http::HttpMethod method, const Headers& headers, const TextCallback& callback)
        : m_URI(URI.c_str())
        , m_method(method)
        , m_headers(headers)
        , m_callback(callback)
    {
    }

    inline TextParameters::TextParameters(const AZStd::string& URI, Aws::Http::HttpMethod method, const Headers& headers, const AZStd::string& body, const TextCallback& callback)
        : m_URI(URI.c_str())
        , m_method(method)
        , m_headers(headers)
        , m_bodyStream( std::make_shared<std::stringstream>(body.c_str()) )
        , m_callback(callback)
    {
    }

    inline TextParameters::TextParameters(TextParameters&& rhs)
        : m_URI(std::move(rhs.m_URI))
        , m_method(std::move(rhs.m_method))
        , m_headers(std::move(rhs.m_headers))
        , m_bodyStream(rhs.m_bodyStream)
        , m_callback(std::move(rhs.m_callback))
    {
    }

    inline TextParameters& TextParameters::operator=(TextParameters&& rhs)
    {
        m_URI = std::move(rhs.m_URI);
        m_method = std::move(rhs.m_method);
        m_headers = std::move(rhs.m_headers);
        m_bodyStream = rhs.m_bodyStream;
        m_callback = std::move(rhs.m_callback);
        return *this;
    }
}
