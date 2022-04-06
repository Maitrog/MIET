<html>
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet"
    integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

<body>
    <h1>{{ $article->title }}</h1>
    <h2>Tags</h2>
    <ul>
        @foreach ($tags as $tag)
            <li>{{ $tag->name }}</li>
        @endforeach
    </ul>
    <b>Id: </b>{{ $article->id }}<p>
    <b>Title: </b>{{ $article->title }}<p>
    <b>Symbol code: </b>{{ $article->symbol_code }}<p>
    <b>Content: </b>{{ $article->content }}<p>
    <b>Created at: </b>{{ $article->created_at }}<p>
    <b>Aoutor: </b>{{ $article->autor }}<p>

</body>

</html>
