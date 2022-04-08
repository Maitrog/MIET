<?php

namespace Database\Factories;

use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Str;

class ArticleFactory extends Factory
{
    public function definition()
    {
        return [
            'title'=> Str::random(10),
            'symbol_code'=> Str::random(10),
            'content'=>Str::random(100),
            'autor'=>$this->faker->name(),
        ];
    }
}