# Cortex
Cortex its a sandbox template for creating web applications in C. It provides a set of functions and types to handle HTTP requests, responses, JSON parsing, and memory management. The main goal of Cortex is to allow developers to create web applications by vibecoding in C, without worrying about the underlying implementation details.

# Create a Web Application with Cortex

## Step 1: Fork these repository
for these repo by clicking in "use as template" and then "fork". This will create a copy of the repository in your GitHub account.

## Step 2: Clone your forked repository
Clone the repository to your local machine using the following command:
```bash
git clone https://github.com/your-username/your-forked-repo.git
```
## Step 3: Pass the [app.c](app.c) file to a llm
copy the content of the [app.c](app.c) file and pass it to a llm (like chatgpt) with a prompt like these:
```markdown
using these sandbox, create a url shortener web application :
endpoints:
- GET /: returns a simple HTML page with a form to submit a URL to be shortened.
- POST /shorten: receives a JSON object with a "url" field and returns a JSON object with a "short_url" field containing the shortened URL.
- GET /redirect/{shortid}: receives a short URL and redirects to the original URL.
storage schema:
store the original urls into a dir called "urls", with these format:
----
urls/
  <shorten_id>.txt
  <shorten_id2>.txt
----
```

## Step 4: Build and run the application
now you can chose from the followin building ways:

### Simple gcc compilation
these template its compilation ready, you can compile the application using gcc with the following command:

```bash
gcc main.c -o app
```
then you can run the application with:
```bash
./app
```

